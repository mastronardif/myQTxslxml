#include "mylist.h"
#include <QTextStream>
#include <QDebug>


const QRegExp myList::kRx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
const QString kStudentAggregatesCols   = "%1,%2,%3,%4,%5";
S_StudentAggregatesHeader myList::StudentAggregateTableDef =
{
    "sid", "StudentId", "RemoteId","name","StudentPointsTotalPercentage", "partic"
};

QString myList::kStudentAggregatesHeader =
             myList::StudentAggregateTableDef.StudentId
        +","+myList::StudentAggregateTableDef.RemoteId
        +","+myList::StudentAggregateTableDef.name
        +","+myList::StudentAggregateTableDef.StudentPointsTotalPercentage
        +","+myList::StudentAggregateTableDef.partic
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


bool caseLessThan_11thCol(const QString &s1, const QString &s2)
{
    // Sort on Cols[E][K] aka [5-1][11-1]
    //QRegExp rx("(\\,)");

    QString ss1, ss2,  ss31, ss32;
    QStringList query; // = s1.split(myList::kRx); //s1.split(rx);  //(myList::kRx);
    query = myList::helperGetColsFromList(s1);

    ss1  = query[4];
    ss31 = query[10];

    //query = s2.split(rx);
    query = myList::helperGetColsFromList(s2);
    ss2  = query[4];
    ss32 = query[10];
    //return ((ss31.toLower() < ss32.toLower()) );
    double d1 = ss31.toDouble();
    double d2 = ss32.toDouble();
    //return (d1 < d2);
    QString  left   = ss1.toLower() + "-A-" + ss31.toLower();
    QString  right  = ss2.toLower() + "-A-" + ss32.toLower();
    //return (left < right );
    return (d1 < d2);
}

struct sortcols
{
    int col1;
    int col2;
} gSortCols;

int gIDCol;
int gP_IDCol;
bool caseInsensitiveLessThan_IDandP_ID(const QString &s1, const QString &s2)
{
    // Sort on Cols[E][K] aka [5-1][11-1]


    //QRegExp rx("(\\,)");

    QString ss11, ss12,  ss21, ss22;
    QStringList query; // = s1.split(rx);  //(myList::kRx);
    query = myList::helperGetColsFromList(s1);

    ss11 = query[gSortCols.col1];
    ss12 = query[gSortCols.col2];

    //query = s2.split(rx);
    query = myList::helperGetColsFromList(s2);
    ss21 = query[gSortCols.col1];
    ss22 = query[gSortCols.col2];
    //return ((ss31.toLower() < ss32.toLower()) );
    int d1 = ss12.toInt();
    int d2 = ss22.toInt();
    //return (d1 < d2);

    QString strD1("a");
    strD1 = strD1.repeated(d1);
    QString strD2("a");
    strD2 = strD2.repeated(d2);

    QString  left   = ss11.toLower() + "-A-" + strD1;
    QString  right  = ss21.toLower() + "-A-" + strD2;

    return (left < right );
}

bool caseInsensitiveLessThan_5ThColAnd11thCol(const QString &s1, const QString &s2)
{
    // Sort on Cols[E][K] aka [5-1][11-1]
    QRegExp rx("(\\,)");

    QString ss1, ss2,  ss31, ss32;
    QStringList query; // = s1.split(rx);  //(myList::kRx);
    query = myList::helperGetColsFromList(s1);

    ss1  = query[4];
    ss31 = query[10];

    //query = s2.split(rx);
    query = myList::helperGetColsFromList(s2);
    ss2  = query[4];
    ss32 = query[10];
    //return ((ss31.toLower() < ss32.toLower()) );
    int d1 = ss31.toInt();
    int d2 = ss32.toInt();
    //return (d1 < d2);

    QString strD1("a");
    strD1 = strD1.repeated(d1);
    QString strD2("a");
    strD2 = strD2.repeated(d2);

    QString  left   = ss1.toLower() + "-A-" + strD1;
    QString  right  = ss2.toLower() + "-A-" + strD2;
    return (left < right );
//    if (d1 == d2)
//    {
//        return (ss1.toLower() < ss2.toLower() );
//    }
//    else
//        false;
//    else
//    {
//        ss1.toLower() < ss2.toLower();
//    }
    //return (ss1.toLower() < ss2.toLower()) && (ss31.toLower() < ss32.toLower());

}

bool caseInsensitiveLessThan_5ThCol(const QString &s1, const QString &s2)
{
    QString ss1, ss2;
    //QRegExp rx("(\\ |\\,|\\.|\\:|\\t)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    //QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'

    //QStringList query = s1.split(rx);
    QStringList query = myList::helperGetColsFromList(s1);
    ss1 = query[4];

    //query = s2.split(rx);
    query = myList::helperGetColsFromList(s2);
    ss2 = query[4];

//    qDebug() << "ss1 = " << ss1;
//    qDebug() << "ss2 = " << ss2;

    //return s1.toLower() < s2.toLower();
    //return ss1.toLower() < ss2.toLower();
    //return ss1.toLower() == ss2.toLower();
    return ss1.toLower() > ss2.toLower();

}

int myList::makeList(S_CourseEntities courseEntities, QString src)
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

    printListToFile("./m_ssn.csv", m_ssn);
    printListToFile("./m_p.csv",   m_p);

    // filter test
    //QStringList QStringList::filter ( const QRegExp & rx ) const
    //QStringList wtf = m_v.filter(QRegExp("#801FF16E"));
    QStringList wtf;
    if (m_v.size() > 0) { wtf.prepend(m_v[0]); }

    printListToFile("801FF16E.csv",  wtf);

    //qSort(m_v.begin(), m_v.end(), qGreater<QString>());
    //qSort(m_v.begin(), m_v.end(), caseInsensitiveLessThan);
    //qSort(m_v.begin(), m_v.end(), caseInsensitiveLessThan_5ThCol);
    //Keep header at the top
    //if(9==0) // skip sort
    {
    QList<QString>::iterator itr = m_v.begin();
    if (m_v.length() > 1) { itr = m_v.begin()+1;}
    printListToFile("./m_v0.csv",   m_v);
    //qSort(itr, m_v.end(), caseLessThan_11thCol);
    //printListToFile("./m_v1.csv",   m_v);

    //qSort(itr, m_v.end(), caseInsensitiveLessThan_5ThCol);

    //qSort(itr, m_v.end(), caseInsensitiveLessThan_5ThColAnd11thCol);
    if (m_v.length() > 0)
    {
        const QStringList labels = helperGetColsFromList(m_v[0]);
        gSortCols.col1 = labels.indexOf("id");
        gSortCols.col2 = labels.indexOf("p_id");
        qSort(itr, m_v.end(), caseInsensitiveLessThan_IDandP_ID);
    }

    }

    //m_v.sort(Qt::CaseInsensitive);
    printListToFile("./m_v.csv",   m_v);

    createListForRemoteIds(courseEntities.m_srcPathRemoteIds, m_remoteIds);
    printListToFile("./m_remoteIds.csv", m_remoteIds);

    createListForStudentNames(courseEntities.m_srcPathStudentNames, m_StudentNames);
    printListToFile("./m_studentNames.csv", m_StudentNames);

    // create roster of remotes/students
    createListForRemoteStudents(m_remoteIds, m_StudentNames, m_rosterRemotesStudents);
    {
    QList<QString>::iterator itr = m_rosterRemotesStudents.begin();
    if (m_rosterRemotesStudents.length() > 1) { itr = m_rosterRemotesStudents.begin()+1;}
    qSort(itr, m_rosterRemotesStudents.end(), caseInsensitiveLessThan_5ThCol);
    }
    printListToFile("./m_rosterRemotesStudents.csv", m_rosterRemotesStudents);

    // create - select student votes outter join where student.id=vote.id
    createListForStudentVotes(m_StudentNames, m_rosterRemotesStudents, m_v, m_StudentVotes);
    printListToFile("./m_StudentVotes.csv", m_StudentVotes);

    // create aggregated lists
    createAggregatedListForStudents(m_ssn, m_v, m_roster, m_aggregatesForStudents);
    //createAggregatedListForStudents(m_v, m_roster, m_aggregatesForStudents);
    printListToFile("./m_aggregatesForStudents.csv",   m_aggregatesForStudents);
    //static int createAggregatedListForStudents(const QStringList list& m_v, const QStringList list& m_roster,  QStringList list m_aggregatesForStudents);

    //createAggregatedListForSession(m_aggregatesForSession);


    return iRetval;
}



int myList::createAggregatedListForStudents(const QStringList& ssn, const QStringList& votes, const QStringList& roster,  QStringList &aggregatesForStudents)
{
    // this is equivalent to a letf outer join.

    QStringList labels;
    QStringList cols;

    // get session parameters
    QString minrep; // minimumum response count.
    int     iMinrep = minrep.toInt();
    QString part;   // participation points.
    if (ssn.length() > 1)
    {
        labels = helperGetColsFromList(ssn[0]);
        cols   = helperGetColsFromList(ssn[1]);

        //part = colsSession[labels.indexOf("part")];
        //ruleMinPart_S = colsSession[labelsSession.indexOf("MinPart_S")];
        minrep = cols[labels.indexOf("minrep")];
        iMinrep = minrep.toInt();
        part   = cols[labels.indexOf("part")];
    }

    QStringList list  = votes; //this->m_courseList.m_v;

    struct S_StudentAggregatesHeader source;

    // Header row
    aggregatesForStudents.append(kStudentAggregatesHeader);


    // sid, name, ...
    QString sId, remoteId, sname;

    if (votes.size() > 0)
    {
        labels = helperGetColsFromList(votes[0]);
    }

    QString previousID = "";
    int iResponses = 0;

    for(int idx = 1; idx < list.length(); idx++)
    {
        // source
        QString line = list[idx];

        cols = myList::helperGetColsFromList(line);

        if (cols.length() < labels.length())
        {
            // skip bad rows
            continue;
        }

        source.StudentId = cols[labels.indexOf("id")];
        source.RemoteId  = cols[labels.indexOf("id")];
        //source.name      = cols[labels.indexOf("ssnn")];

        //"StudentId", "RemoteId", "name", "StudentPointsTotalPercentage" // ....
        if (previousID.compare(source.StudentId, Qt::CaseInsensitive) != 0)
        {
            // get distinct rows
            previousID = source.StudentId;

            // clear
            {
                iResponses = 0;
                source.partic = "";// iResponses;
            }
        }

        // calc participation.  How many question responded to.
        QString fans = cols[labels.indexOf("fans")];

        if (fans.length() > 0)
        {
            iResponses++;
            source.partic = QString::number(iResponses);            
        }
        //
        bool bPassMinimumPartic = (iResponses > 0 && (iResponses >= iMinrep) ) ? true : false;
        source.partic =  bPassMinimumPartic ? part : "0";
        //

//        QString row = QString(kStudentAggregatesCols).arg(
//                    source.StudentId, source.RemoteId,
//                    source.name, "TBD", source.partic);

        //aggregatesForStudents.append(row);
        S_StudentAggregatesHeader::appendOrUpdate(source.RemoteId, source, aggregatesForStudents);

        previousID = source.StudentId;
    }
}

int myList::createListForRemoteIds(const QString pathRemoteIds, QStringList &destRoster)
{
    int iRetval = 0; // default success

    qDebug() << "pathRemoteIds = " << pathRemoteIds;

    QFile file(pathRemoteIds);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    //foreach (const QString &line, list)
    QTextStream in(&file);
    destRoster << "RemoteId,StudentId";
    while (!in.atEnd())
    {
        QString line = in.readLine();
 //       if (line.contains(rx3))
        {
            destRoster << line;
            //qDebug() << line;
        }
    }

    // optional, as QFile destructor will already do it:
    file.close();

    return iRetval;
}

int myList::createListForRemoteStudents(const QStringList& remoteIds, const QStringList& studentNames, QStringList& destRosterRemotesStudents)
{
    int iRetval = 0; // default success

    // RemoteId,StudentId,Last Name, First Name, Username
    //destRosterRemotesStudents << remoteIds[0] + "," + studentNames[0];
    QString strRids = helperGetColsFromList(remoteIds[0]).join(',');
    QString strSids = helperGetColsFromList(studentNames[0]).join(',');
    destRosterRemotesStudents << strRids + "," + strSids;
    //destRosterRemotesStudents << remoteIds[0] + "," + studentNames[0];
       
    QStringList newRows;

    // fix destinaton.
    for(int idx = 1; idx < remoteIds.length(); idx++)
    {
        strRids = helperGetColsFromList(remoteIds[idx]).join(',');
        destRosterRemotesStudents << strRids + "," + "null,null,null";
        //destRosterRemotesStudents << remoteIds[idx] + "," + "null,null,null";
    }

    // find and update.
    for(int idx = 1; idx < studentNames.length(); idx++)
    {
        // find and update.
        if(eNOTFOUND == helperFindAndUpdate(destRosterRemotesStudents, studentNames[idx]))
        {
            QStringList list = helperGetColsFromList(studentNames[idx]);
            QString studentNames = list.join(',');

            helperTrimmed(list);
            newRows.append("null,null," + studentNames); //studentNames[idx]);
        }
    }

    // append newRows if any
    if(!newRows.isEmpty())
    {
        destRosterRemotesStudents.append(newRows);
    }

    return iRetval;
}

int myList::createListForStudentNames(const QString pathStudentNames, QStringList &destStudentNames)
{
    int iRetval = 0; // default success
    destStudentNames <<  "Last Name, First Name, Username";
    qDebug() << "pathStudentNames = " << pathStudentNames;

    QFile file(pathStudentNames);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    if (!file.exists())
    {
        //destStudentNames <<  "Last Name, First Name, Username";
        return 1;
    }

    //foreach (const QString &line, list)
    QTextStream in(&file);
    //destRoster << "RemoteId,StudentId";
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();

        if (line.startsWith('!')) {continue;}

        destStudentNames << line;
    }

    // optional, as QFile destructor will already do it:
    file.close();

    return iRetval;
}

int myList::createListOfStudentsAbscent(const QStringList& students, const QStringList& rosterRemotesStudents, const QMap<QString, int> uniqueClickerIds,
                                        QStringList& studentsAbscent)
{
    // list students that did not vote.

    studentsAbscent.clear();

    // For each student in the roster that did NOT vote.  You were abscent.
    const QStringList labels = helperGetColsFromList(students[0]);
    for (int idx = 1; idx < students.length(); idx++)
    {
        QString line = students[idx];
        QStringList cols = helperGetColsFromList(line);

        if (cols.length() < labels.length())  // be safe
        {
            // skip bad rows
            continue;
        }

        QString sid = cols[labels.indexOf("Username")];
        QStringList find;
        find << "RemoteId";

        QStringList studentClickers = helperFindByKeyValue(rosterRemotesStudents, find, "Username", sid);

        // list = find matches in roster/students table.
        bool bVoted = false;
        foreach(QString sid, studentClickers)
        {
            if(uniqueClickerIds.contains(sid))
            {
                bVoted = true;
                break;
            }
        }

        if (!bVoted)
        {
            studentsAbscent.append(line + "," + studentClickers.join(','));
        }
    }

    return studentsAbscent.count();
}

int myList::createListForStudentVotes(const QStringList& students, const QStringList& rosterRemotesStudents, const QStringList& votes,
                                      QStringList& StudentVotes)
{
    int iCount = 0; // count of students votes includes unregiste votes.
    StudentVotes.clear();

    QMap<QString, int> uniqueClickerIds;

    QStringList labels;
    if (votes.length() > 0) {
        labels = helperGetColsFromList(votes[0]);
    }
    QStringList cols;

    for(int idx = 1; idx < votes.length(); idx++)
    {
        QString line = votes[idx];
        cols = helperGetColsFromList(line); //line.split(myList::kRx);

        if (cols.length() < labels.length())
        {
            // skip bad rows
            continue;
        }

        QString clickerId = cols[labels.indexOf("id")];
        uniqueClickerIds.insert(clickerId, idx);
    }

    StudentVotes.append("Last Name,First Name,StudentId,RemoteId");
    foreach(QString clickerId, uniqueClickerIds.keys())
    {
        QStringList find;
        find << "Last Name" << "First Name" << "StudentId" << "RemoteId";
        QStringList results = helperFindByKeyValue(rosterRemotesStudents, find, "RemoteId", clickerId);

        if (results.length() == 0)
        {
            // not found in the roster.
            results << "null" << "null" << "null" << clickerId;
        }

        StudentVotes.append(results.join(','));
    }

    // list students that did not vote.

    QStringList studentsAbscent;

    createListOfStudentsAbscent(students, rosterRemotesStudents, uniqueClickerIds, studentsAbscent);
//qDebug() << "abscenties:\n" << studentsAbscent;
StudentVotes << "abscent(s)";
    StudentVotes << studentsAbscent;

    return iCount;
}

void myList::helperTrimmed(QStringList& list)
{
    for (int idx = 0; idx < list.length(); idx++)
    {
        list[idx].remove('"');
        list[idx] = list[idx].trimmed();
    }
}

QStringList countQuotedStrings(const QString comaList)
{
    QString str = comaList;
    QRegExp rx3("\"([^\"]*)\",*");

    //qDebug() << "str = " << str;
    //int pos = rx3.indexIn(str);

    QStringList list;
    int pos = 0;

    while ((pos = rx3.indexIn(str, pos)) != -1) {
        list << rx3.cap(1);
        pos += rx3.matchedLength();
    }

    //QStringList list = rx3.capturedTexts();
    //qDebug() << "list = "<< list;

    return list; //.count();
}

const QStringList myList::helperGetColsFromList(const QString comaList)
{
    QRegExp  rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'

    QStringList list;
    list = countQuotedStrings(comaList);

    QStringList query;// = comaList.split(rx);

    //query = comaList.split(rx);
    if (list.count() > 0) {
        query = list;
    }
    else {
        query = comaList.split(rx);
    }

    helperTrimmed(query);

    return query;
}

myList::eTerms myList::helperFindAndUpdate(QStringList& destRosterRemotesStudents, const QString studentNames)
{
    eTerms eRetval = eNOTFOUND;

    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'

    // "Last Name, First Name, Username"
    const QString labelsStudentNames = "Last Name, First Name, Username";
    QStringList srcLabels = myList::helperGetColsFromList(labelsStudentNames);

    QStringList srcCols = studentNames.split(rx);
    helperTrimmed(srcCols);

    QString Uname = (srcLabels.indexOf("Username")   != -1) ? srcCols[srcLabels.indexOf("Username")]   : "null";

    //qDebug() << rid;

    // find rid in _____. //this may be slow if so do it another way.
    //labels.clear();
    QStringList destLabels;
    QStringList destCols;
    destLabels = myList::helperGetColsFromList(destRosterRemotesStudents[0]);
    for (int idx = 1; idx < destRosterRemotesStudents.length(); idx++)
    {
        destCols = destRosterRemotesStudents[idx].split(rx);
        helperTrimmed(destCols);

        QString StudentId = destCols[destLabels.indexOf("StudentId")];
        //qDebug() << "RemoteId = " << RemoteId;
        if (0 == StudentId.compare(Uname))
        {
            eRetval = eFOUND;
//            qDebug() << "*** match RemoteId = " << StudentId
//                     << destCols
//                     << studentNames;
            destCols[destLabels.indexOf("Username")]   = srcCols[srcLabels.indexOf("Username")];
            destCols[destLabels.indexOf("First Name")] = srcCols[srcLabels.indexOf("First Name")];
            destCols[destLabels.indexOf("Last Name")]  = srcCols[srcLabels.indexOf("Last Name")];
            destRosterRemotesStudents[idx] = destCols.join(',');

            //qDebug() << " destRosterRemotesStudents[idx] = " <<  destRosterRemotesStudents[idx];
        }
    }

    return eRetval;
}

QStringList myList::helperFindByKeyValue(const QStringList list, const QStringList whatToFind, const QString keyName, const QString keyValue)
{
    QStringList retval;
    QStringList labels = myList::helperGetColsFromList(list[0]);
//qDebug() << "whatToFind = "<< whatToFind;
    foreach (QString findWhat,  whatToFind)
    {
        if (labels.indexOf(findWhat) == -1)
        {
           return retval;
        }
    }

    if (labels.indexOf(keyName) == -1)
    {
        return retval;
    }

//qDebug() << "whatToFind = " << whatToFind;
//qDebug() << "keyName = "    << keyName;
//qDebug() << "keyValue = "   << keyValue;

    QStringList cols;
    for (int idx = 1; idx < list.length(); idx++)
    {
        cols = list[idx].split(kRx);
        helperTrimmed(cols);
        cols = myList::helperGetColsFromList(list[idx]);

        QString value = cols[labels.indexOf(keyName)];
        if (value.compare(keyValue, Qt::CaseInsensitive) == 0)
        {
            foreach (QString findWhat,  whatToFind)
            {
                value = cols[labels.indexOf(findWhat)];
                retval.append(value);
            }
        }
    }

    //list.filter()

    return retval;
}

int myList::helperFindIndexByKey( const QStringList list, const QString keyName, const QString keyValue)
{
    int iIndex = -1;

    QStringList labels = myList::helperGetColsFromList(list[0]);

    if (list.length() < 1) { return iIndex; }

    for (int idx = 1; idx < list.length(); idx++)
    {
        QStringList cols = myList::helperGetColsFromList(list[idx]);

        if (cols.length() < labels.length())
        {
            // skip bad rows
            continue;
        }

        QString value = cols[labels.indexOf(keyName)];
        if (keyValue.compare(value, Qt::CaseInsensitive) == 0)
        {
            return idx;
        }
    }

    return iIndex;

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

int S_StudentAggregatesHeader::appendOrUpdate(const QString inRemoteID, const S_StudentAggregatesHeader &source, QStringList &dest)
{
   int idx = 0;

   QString row = QString(kStudentAggregatesCols).arg(
               source.StudentId, source.RemoteId,
               source.name, "TBD", source.partic);

   QStringList labels;
   if (dest.size() > 0)
   {
       labels = myList::helperGetColsFromList(dest[0]);
   }

   QStringList cols;

   // find and update
   for (idx = 1; idx < dest.length(); idx++)
   {
       cols = myList::helperGetColsFromList(dest[idx]);

       if (cols.length() < labels.length())
       {
           // skip bad rows
           continue;
       }

       QString remoteID = cols[labels.indexOf("RemoteId")];

       if (remoteID.compare(inRemoteID, Qt::CaseInsensitive) == 0)
       {
           dest[idx] = row;
           return idx;
       }
   }

   // not found
   dest.append(row);

   return idx;

}

