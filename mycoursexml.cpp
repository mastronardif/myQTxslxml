#include "mycoursexml.h"
#include <QFile>
#include <QDebug>
#include <QString>


myCourseXml::myCourseXml(myList &courseList) : m_courseList(courseList)
{

    // TBD pass these in the constructor.
    srcPathFolder      = "/Users/frank.mastronardi/workspace/iclicker740Sources/Debug/Classes/0Large_PHIL 102";

    //m_srcPathRemoteIds =  srcPathFolder + "/SessionData/" + "RemoteID.csv";
    srcFolderName = "0Large_PHIL 102";

    srcFileName   = "L1501291001.xml";

    m_pathImageFolder = QString("%1/%2/").arg(srcPathFolder, "Images");
}


int myCourseXml::printSession()
{
    int iRetval = 0; // default success
    QString outFN = "./poc_01.xml";
    struct helperMyCourseXmlErr err;
    QFile::FileError eErr;

    QFile file(outFN);


    if (!file.open(QIODevice::WriteOnly))
    {
        //QFile::error()
        err.msg    = file.errorString();
        eErr   = file.error();
        err.msg = QString("%1, CreateXMLFile_StudentSummary() = %2, %3\n").arg(outFN, err.msg,  QString::number(eErr));
        qDebug() << err.msg ;
        //QMessageBox::warning(0, "", errMsg);
        return -1;
    }

    QXmlStreamWriter* xmlWriter = new QXmlStreamWriter();
    xmlWriter->setDevice(&file);
    xmlWriter->setAutoFormatting(true);
    xmlWriter->writeStartDocument();

    xmlWriter->writeStartElement("ROOT"); xmlWriter->writeAttribute("SSR",   "makeThistheRootTag");

    xmlWriter->writeStartElement("SESSION");
    writeSessionAttributes(xmlWriter, this->m_courseList.m_ssn);

    // Title

    //xmlWriter->writeAttribute("NAME",
    writeTitleElement(xmlWriter, this->m_courseList.m_ssn);


    // Questions
    xmlWriter->writeStartElement("QUESTIONS");   // <QUESTIONS>

    QStringList partList = srcFileName.split(".");
    QString withoutExtension = partList[0];

    forEachQuestion(xmlWriter, this->m_courseList.m_p, m_pathImageFolder, withoutExtension);

    xmlWriter->writeEndElement();   // </QUESTIONS>

    xmlWriter->writeStartElement("STUDENTS");   // <STUDENTS>

    // foreach student
    //forEachStudent(xmlWriter, this->m_courseList.m_v);
    forEachStudent(xmlWriter, this->m_courseList, this->m_courseList.m_v);
    qDebug() << "report on these students:";
    //myList::printList(this->m_courseList.m_StudentVotes);
    //forEachStudent(xmlWriter, this->m_courseList, this->m_courseList.m_StudentNames, this->m_courseList.m_v);

    xmlWriter->writeEndElement();   // </STUDENTS>

    xmlWriter->writeEndElement();   // </SESSION>

    xmlWriter->writeEndElement();   // </ROOT>

    return iRetval;
}

int myCourseXml::writeHdrElement(QXmlStreamWriter* xmlWriter, QStringList ColsToShow)
{
    //ColsToShow << "@name" << "@StudentId" << "@RemoteId";
    xmlWriter->writeStartElement("Hdr"); // <Hdr>
        if (ColsToShow.contains("@name", Qt::CaseInsensitive))
        {
            xmlWriter->writeStartElement("col"); // <col>
                xmlWriter->writeAttribute("attrib", "@name");
                xmlWriter->writeAttribute("n", "Name");
            xmlWriter->writeEndElement(); // </col>
        }
        if (ColsToShow.contains("@StudentId", Qt::CaseInsensitive))
        {
            xmlWriter->writeStartElement("col"); // <col>
                xmlWriter->writeAttribute("attrib", "@StudentId");
                xmlWriter->writeAttribute("n", "Student ID");
            xmlWriter->writeEndElement(); // </col>
        }

        if (ColsToShow.contains("@RemoteId", Qt::CaseInsensitive))
        {
            xmlWriter->writeStartElement("col"); // <col>
                xmlWriter->writeAttribute("attrib", "@RemoteId");
                xmlWriter->writeAttribute("n", "Remote or GO ID");
            xmlWriter->writeEndElement(); // </col>
        }

    xmlWriter->writeEndElement(); // </Hdr>
}

int myCourseXml::writeTitleElement(QXmlStreamWriter* xmlWriter, const QStringList &session)
{
    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QStringList list  = session;

    const QStringList labels = myList::helperGetHeaderLabels(session[0]);
    QStringList cols = list[1].split(rx);

    // skip 1st row aka the header
    QString name   = (labels.indexOf("ssnn")   != -1) ? cols[labels.indexOf("ssnn")]   : "null";
    name.remove('"');

    xmlWriter->writeStartElement("TITLE");

    xmlWriter->writeAttribute("NAME", name);

    xmlWriter->writeTextElement("SESSION", "TBD");
    QString sd = "Generated: "+ QDateTime::currentDateTime().toString("MM/dd/yyyy h:m:s");

    xmlWriter->writeTextElement("sdate", sd);

    // Write HdrElement
    QStringList ColsToShow;
    ColsToShow << "@name" << "@StudentId" << "@RemoteId";
    myCourseXml::writeHdrElement(xmlWriter, ColsToShow);

    xmlWriter->writeTextElement("DATE", "3/24/15 10:01 AM");
    xmlWriter->writeTextElement("SESSIONID", "sessionIndex-0");
//    <TITLE NAME="Q2 1/29 and 2/3">
//        <SESSION>0Large_PHIL 102</SESSION>
//        <sdate>Generated: 03/11/2015 16:55:25</sdate>
//        <Hdr>
//            <col attrib="@name" n="Name"/>
//            <col attrib="@StudentId" n="Student ID"/>
//            <col attrib="@RemoteId" n="Remote or GO ID"/>
//        </Hdr>
//        <DATE>1/29/15 10:01 AM</DATE>
//        <SESSIONID>sessionIndex-0</SESSIONID>
//    </TITLE>

    xmlWriter->writeEndElement(); // </TITLE>
}

int myCourseXml::writeSessionAttributes(QXmlStreamWriter* xmlWriter, const QStringList &session)
{
    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QStringList list  = session;

    const QStringList labels = myList::helperGetHeaderLabels(session[0]);
    QStringList cols = list[1].split(rx);

    // skip 1st row aka the header
    for(int idx = 1; idx < list.length(); idx++)
    {
        QString line = list[idx];

        cols = line.split(rx);
        if (cols.length() != labels.length())
        {
            //skip bad rows.
            continue;
        }

        QString name   = (labels.indexOf("ssnn")   != -1) ? cols[labels.indexOf("ssnn")]   : "null";
        QString part = (labels.indexOf("part") != -1) ? cols[labels.indexOf("part")] : "null";
        name.remove('"'); part.remove('"');

        xmlWriter->writeAttribute("part", part);
        //Partic="0.00" ap="0.71" avg="2.85" part="0.00" perf="4.00" pp="4.00" sppp="4.00"
        xmlWriter->writeAttribute("Partic", "0.00");
        xmlWriter->writeAttribute("ap", "0.71");
        xmlWriter->writeAttribute("avg", "2.85");
        //xmlWriter->writeAttribute("part", "0.00");
        xmlWriter->writeAttribute("perf", "4.00");
        xmlWriter->writeAttribute("pp", "4.00");
        xmlWriter->writeAttribute("sppp", "4.00");
    }


}

int myCourseXml::writeAggregatesForStudent(QXmlStreamWriter* xmlWriter, const QString sid, const QStringList &list)
{    
    xmlWriter->writeAttribute("ClassAveragePerformancePercentage", "0,00");
    xmlWriter->writeAttribute("ClassAveragePointsPerformance",       "15.64");
    xmlWriter->writeAttribute("ClassAveragePointsTotal",       "45.99");
    xmlWriter->writeAttribute("ClassAveragePointsTotalPercentage",       "15.64");
    xmlWriter->writeAttribute("Partic",       "0.00");
    xmlWriter->writeAttribute("Perform",       "4,707.00");
    xmlWriter->writeAttribute("PossiblePointsParticipation",       "0.00");
    xmlWriter->writeAttribute("PossiblePointsPerformance",       "9.00");
    xmlWriter->writeAttribute("PossiblePointsTotal",       "34.00");
    xmlWriter->writeAttribute("StudentPointsParticipation",       "0.00");
    xmlWriter->writeAttribute("StudentPointsPerformance",       "34.00");
    xmlWriter->writeAttribute("StudentPointsPerformancePercentage",       "45.99");
    xmlWriter->writeAttribute("StudentPointsTotalPercentage",       "9.00");
    xmlWriter->writeAttribute("Total",       "4,707.00");

    xmlWriter->writeAttribute("n",       "look up name");
    //xmlWriter->writeAttribute("name",       "tbd");

    xmlWriter->writeAttribute("partipationtotal",       "0.00");
    xmlWriter->writeAttribute("rid",       "");
    xmlWriter->writeAttribute("scorepercent",       "999.99");
    xmlWriter->writeAttribute("studentperf",                         "16.00");
    xmlWriter->writeAttribute("studentperfpercent",                  "47.06");
}

int myCourseXml::writeStudentAttributes(QXmlStreamWriter* xmlWriter, const myList& ssnData, const QString rId)
{
    xmlWriter->writeAttribute("sid",  rId);

    xmlWriter->writeAttribute("RemoteId",  rId);

    // lookup name by studentId.
    QStringList find;
    find << "StudentId" << "Last Name" << "First Name";
    QStringList results = myList::helperFindByKeyValue(ssnData.m_rosterRemotesStudents, find, "RemoteId", rId);
    QString name;
    QString studentId;
    if (results.length() == 3)
    {
        studentId = results[0];
        name = results[1] + ' ' + results[2];
    }

    xmlWriter->writeAttribute("StudentId",  studentId);
    xmlWriter->writeAttribute("name", name);
}

int myCourseXml::forEachQuestion(QXmlStreamWriter* xmlWriter, const QStringList &questions, const QString srcPathImageFolder, const QString srcFileName)
{
    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QStringList list  = questions; //this->m_courseList.m_p;

    const QStringList labels = myList::helperGetHeaderLabels(questions[0]);
    QStringList cols = list[1].split(rx);

    for(int idx = 1; idx < list.length(); idx++)
    {
        QString line = list[idx];

        cols = line.split(rx);
        if (cols.length() != labels.length())
        {
            //skip bad rows.
            continue;
        }

        QString qn   = (labels.indexOf("qn")   != -1) ? cols[labels.indexOf("qn")]   : "null";
        QString cans = (labels.indexOf("cans") != -1) ? cols[labels.indexOf("cans")] : "null";
        qn.remove('"'); cans.remove('"');
        xmlWriter->writeStartElement("question");
        xmlWriter->writeAttribute("name", qn);
        xmlWriter->writeAttribute("CorrectAnswer",   cans);

        QString id = QString("q%1").arg(QString::number(idx));
        xmlWriter->writeAttribute("id", id);

        QString questionFileName = QString("%1_Q%2.jpg").arg(srcFileName, QString::number(idx));
        QString path = QString("%1%2").arg(srcPathImageFolder, questionFileName);
        xmlWriter->writeAttribute("desktopImage",  path);
        xmlWriter->writeAttribute("file",          questionFileName);

        // TBD write question attributes
        //<question AveragePercent="0.00" AveragePoints="0.00" CorrectAnswer="" CorrectResponses="0"
        //IncorrectResponses="0" NoResponses="0" Responses="262" desktopImage="/Users/frank.mastronardi/workspace/iclicker740Sources/Debug/Classes/0Large_PHIL 102/Images/L1501291001_Q1.jpg" file="L1501291001_Q1.jpg"
        //id="q1" name="Question 1" possiblePoints="1.00" pp="1.00"/>
        xmlWriter->writeAttribute("AveragePercent",  "0.00");
        xmlWriter->writeAttribute("AveragePoints",  "0.00");
        xmlWriter->writeAttribute("CorrectResponses",  "0");
        xmlWriter->writeAttribute("IncorrectResponses",  "0");
        xmlWriter->writeAttribute("NoResponses",  "0");
        xmlWriter->writeAttribute("Responses",  "262");
        xmlWriter->writeAttribute("possiblePoints",  "1.00");
        xmlWriter->writeAttribute("pp",  "1.00");


        xmlWriter->writeEndElement(); // </question>
    }
}

//int myCourseXml::forEachStudent(QXmlStreamWriter* xmlWriter, const QStringList &votes)
int myCourseXml::forEachStudent(QXmlStreamWriter* xmlWriter,  const myList& ssnData, const QStringList &votes)
{
    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QStringList list  = votes; //this->m_courseList.m_v;

    const QStringList labels = myList::helperGetHeaderLabels(votes[0]);
    QStringList coloumns = list[1].split(rx);

    int studentCount=1;
    for(int idx = 1; idx < list.length();)//idx++)
    {
        QString line = list[idx];

        coloumns = line.split(rx);
        QString rId = (coloumns.length() == labels.length()) ? coloumns[labels.indexOf("id")] : "null";

        rId.remove('"');

        xmlWriter->writeStartElement("student");   //<student>
        writeStudentAttributes(xmlWriter, ssnData, rId);
        //writeStudentAttributes(xmlWriter, ss1);
        xmlWriter->writeAttribute("idx",  QString::number(studentCount++));
        {
            QStringList studentAgregates;  // calc agregates
            writeAggregatesForStudent(xmlWriter, rId, studentAgregates);
            //writeStudentAggregatesForStudent(sid); // BySession
            //writeSessionAggregatesForSession(thisSession);
        }


        xmlWriter->writeStartElement("qr");   //<qr>
        forEachStudentVote(idx, rId, list, xmlWriter);
        //orEachStudentVote(idx, rId, list, xmlWriter);
        xmlWriter->writeEndElement();        // </qr>

        xmlWriter->writeEndElement();  // </student>
//        qDebug() << "BBBBBBBB________" << idx; // << total;
//        qDebug() << "idx = " << idx;
    }
}

int myCourseXml::forEachStudentVote(int &idx, const QString argStudent, const QStringList &list, QXmlStreamWriter* xmlWriter)
{
    const QStringList labels = myList::helperGetHeaderLabels(list[0]);
    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QString clean;
    QString student = argStudent;
    student.remove('"');

    for(; idx < list.length(); idx++)
    {
        QString line = list[idx];

        QStringList cols = line.split(rx);
        //QString ss1 = (coloumns.length() > 3) ? coloumns[4]  : "null";
        QString ss1 = (cols.length() == labels.length()) ? cols[labels.indexOf("id")]   : "null";
        QString qid = (cols.length() == labels.length()) ? cols[labels.indexOf("p_id")] : "null";
        QString scr = (cols.length() == labels.length()) ? cols[labels.indexOf("scr")]  : "null";
        QString ans = (cols.length() == labels.length()) ? cols[labels.indexOf("ans")]  : "null";

        ss1.remove('"');
        qid.remove('"');
        qid = QString("q%1").arg(qid);
        scr.remove('"');
        ans.remove('"');

        if (QString::compare(ss1, student, Qt::CaseInsensitive) != 0) { break; }

        //qDebug() << student << ss1 << qid << "ss1 = " << ss1 << "qid = " << qid << "scr = " << scr;


        xmlWriter->writeStartElement("q");   // <q>
        //xmlWriter->writeAttribute("sid",  ss1);
        xmlWriter->writeAttribute("id",  qid);
        //xmlWriter->writeAttribute("scr",  scr);
        xmlWriter->writeAttribute("score",  "0");
        xmlWriter->writeAttribute("vote", ans);
        xmlWriter->writeAttribute("Response", ans);
        xmlWriter->writeAttribute("icr", "tbd");
        xmlWriter->writeEndElement(); // </q>

    }

}
