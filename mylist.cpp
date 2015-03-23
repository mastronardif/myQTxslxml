#include "mylist.h"
#include <QTextStream>
#include <QDebug>

const QString kStudentAggregatesCols   = "%1,%2,%3,%4";
S_StudentAggregatesHeader myList::StudentAggregateTableDef =
{
    "sid", "StudentId", "RemoteId","name","StudentPointsTotalPercentage"
};

QString myList::kStudentAggregatesHeader =
             myList::StudentAggregateTableDef.StudentId
        +","+myList::StudentAggregateTableDef.RemoteId
        +","+myList::StudentAggregateTableDef.name
        +","+myList::StudentAggregateTableDef.StudentPointsTotalPercentage
        ;

myList::myList()
{
    this->m_course = QStringList();
 //   qDebug() << myList::StudentAggregateTableDef.sid << myList::StudentAggregateTableDef.StudentId;
}

bool caseInsensitiveLessThan(const QString &s1, const QString &s2)
{
    return s1.toLower() < s2.toLower();
}
bool caseInsensitiveLessThan_5ThCol(const QString &s1, const QString &s2)
{
    QString ss1, ss2;
    //QRegExp rx("(\\ |\\,|\\.|\\:|\\t)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'

    QStringList query = s1.split(rx);
    ss1 = (query.length() > 4) ? query[4] : query[0];

    query = s2.split(rx);
    ss2 = (query.length() > 4) ? query[4] : query[0];

//    qDebug() << "ss1 = " << ss1;
//    qDebug() << "ss2 = " << ss2;

    //return s1.toLower() < s2.toLower();
    return ss1.toLower() < ss2.toLower();

}

int myList::makeList(QString src)
{
    int iRetval = 0;
    QTextStream stream(&src);
    QStringList *ptrList = &m_course;
    QString line;

    QRegExp rx3("(BEGIN|END)");
    rx3.setMinimal(true);
    rx3.setCaseSensitivity(Qt::CaseInsensitive);

    do
    {
        line = stream.readLine();

        // sw/ on course entity ie. session, pole, vote
        if(line.contains(QRegExp("BEGIN \\[SSN\\]")))
        {
            ptrList = &m_ssn;
            continue;   // skip BEGIN line
        }
        if(line.contains(QRegExp("BEGIN \\[SSN/P\\]")))
        {
            ptrList = &m_p;
            continue;   // skip BEGIN line
        }
        if(line.contains(QRegExp("BEGIN \\[SSN/P/v\\]", Qt::CaseInsensitive)))
        {
            ptrList = &m_v;
            continue;   // skip BEGIN line
        }

        // skip blanks, and END marker
        if ((line.contains(QRegExp("END \\[SSN\\]", Qt::CaseInsensitive)))  ||
            (line.contains(QRegExp("END \\[SSN/P\\]", Qt::CaseInsensitive)))||
            (line.contains(QRegExp("END \\[SSN/P/v\\]", Qt::CaseInsensitive))) )
        {
            continue;   // skip BEGIN line
        }

        if (0 == line.trimmed().length())
        {
            continue; // skip blank lines
        }

        *ptrList << line;

        //qDebug() << line;

    } while(!line.isNull());

//    do
//    {
//        line = stream.readLine();
//        m_course << line;
//        qDebug() << line;
//    } while(!line.isNull());

    // test list
    //qDebug() << "m_course BEGIN"; printList(m_course); qDebug() << "m_course END";

    //printList(m_p);printList(m_p);printList(m_v);
//    qDebug() << "m_ssn BEGIN"; printList(m_ssn); qDebug() << "m_ssn END";
//    qDebug() << "m_p BEGIN"; printList(m_p); qDebug() << "m_p END";
//    qDebug() << "m_v BEGIN"; printList(m_v); qDebug() << "m_v END";

    printListToFile("./m_ssn.csv", m_ssn);
    printListToFile("./m_p.csv",   m_p);

    //qSort(m_v.begin(), m_v.end(), qGreater<QString>());
    //qSort(m_v.begin(), m_v.end(), caseInsensitiveLessThan);
    //qSort(m_v.begin(), m_v.end(), caseInsensitiveLessThan_5ThCol);
    //Keep header at the top
    //if(9==0) // skip sort
    {
    QList<QString>::iterator itr = m_v.begin();
    if (m_v.length() > 1) { itr = m_v.begin()+1;}
    qSort(itr, m_v.end(), caseInsensitiveLessThan_5ThCol);
    }

    //m_v.sort(Qt::CaseInsensitive);
    printListToFile("./m_v.csv",   m_v);

    // filter test
    //QStringList QStringList::filter ( const QRegExp & rx ) const
    QStringList wtf = m_v.filter(QRegExp("#970F6BF3"));
    wtf.prepend(m_v[1]);
    printListToFile("970F6BF3.csv",  wtf);

    //CreateListForRoster(m_roster);

    // create aggregated lists
    createAggregatedListForStudents(m_v, m_roster, m_aggregatesForStudents);
    printListToFile("./m_aggregatesForStudents.csv",   m_aggregatesForStudents);
    //static int createAggregatedListForStudents(const QStringList list& m_v, const QStringList list& m_roster,  QStringList list m_aggregatesForStudents);

    //createAggregatedListForSession(m_aggregatesForSession);


    return iRetval;
}



int myList::createAggregatedListForStudents(const QStringList& votes, const QStringList& roster,  QStringList &aggregatesForStudents)
{
    // this is equivalent to a letf outer join.
    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QStringList list  = votes; //this->m_courseList.m_v;

    struct S_StudentAggregatesHeader source;

    // Header row
    aggregatesForStudents.append(kStudentAggregatesHeader);


    // sid, name, ...
    QString sId, remoteId, sname;

    const QStringList labels = helperGetHeaderLabels(votes[0]);
    QStringList cols; // = list[1].split(rx);

    QString lastKnown = "";
    //foreach (const QString &line, list)
    for(int idx = 1; idx < list.length(); idx++)
    {
        // source
        QString line = list[idx];
        cols = line.split(rx);

        if (cols.length() < labels.length())
        {
            // skip bad rows
            continue;
        }


        source.StudentId = (cols.length() == labels.length()) ? cols[labels.indexOf("id")] : "null";
        source.RemoteId  = (cols.length() == labels.length()) ? cols[labels.indexOf("id")] : "null";
        source.name      = (labels.indexOf("ssnn")   != -1) ? cols[labels.indexOf("ssnn")]   : "null";
        source.StudentId.remove('"'); source.RemoteId.remove('"'); source.name.remove('"');
  //"StudentId", "RemoteId", "name", "StudentPointsTotalPercentage" // ....

        if (lastKnown.compare(source.StudentId, Qt::CaseInsensitive) == 0)
        {
            // get distinct rows
            lastKnown = source.StudentId;
            continue;
        }

        lastKnown = source.StudentId;

        QString row = QString(kStudentAggregatesCols).arg(
                    source.StudentId, source.RemoteId,
                    source.name, "TBD");

        aggregatesForStudents.append(row);
    }


}

int myList::printListToFile(QString fn, QStringList list)
{
    int iRetval = 0;

    QFile file(fn);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    foreach (const QString &line, list)
    {
 //       if (line.contains(rx3))
        {
            out << line << "\n";
        }
    }

    // optional, as QFile destructor will already do it:
    file.close();

    return iRetval;
}

int myList::printList(QStringList list)
{
    int iCnt = 0;
     QRegExp rx3("(BEGIN|END)");
     rx3.setMinimal(true);
     rx3.setCaseSensitivity(Qt::CaseInsensitive);

    foreach (const QString &line, list) {
 //       if (line.contains(rx3))
        {
            qDebug() << line;
        }
        iCnt++;
    }

    return iCnt;
}

const QStringList myList::helperGetHeaderLabels(const QString list)
{
    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QStringList query = list.split(rx);
    for(int idx = 0; idx < query.length(); idx++)
    {
        query[idx].remove('"');
    }

    return query;
}
