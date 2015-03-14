#include "mylist.h"
#include <QTextStream>
#include <QDebug>


myList::myList()
{
    this->m_course = QStringList();

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
        }
        if(line.contains(QRegExp("BEGIN \\[SSN/P\\]")))
        {
            ptrList = &m_p;
        }
        if(line.contains(QRegExp("BEGIN \\[SSN/P/v\\]", Qt::CaseInsensitive)))
        {
            ptrList = &m_v;
            continue;   // skip BEGIN line
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
    QList<QString>::iterator itr = m_v.begin();
    if (m_v.length() > 1) { itr = m_v.begin()+1;}
    qSort(itr, m_v.end(), caseInsensitiveLessThan_5ThCol);

    //m_v.sort(Qt::CaseInsensitive);
    printListToFile("./m_v.csv",   m_v);

    // filter test
    //QStringList QStringList::filter ( const QRegExp & rx ) const
    QStringList wtf = m_v.filter(QRegExp("#970F6BF3"));
    wtf.prepend(m_v[1]);
    printListToFile("970F6BF3.csv",  wtf);


    return iRetval;
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

