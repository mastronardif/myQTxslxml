﻿#include "mycoursexml.h"
#include <QFile>
#include <QDebug>
#include <QString>


myCourseXml::myCourseXml(myList &courseList) : m_courseList(courseList)
{
    // TBD pass these in the constructor.
    srcPathFolder = "/Users/frank.mastronardi/workspace/iclicker740Sources/Debug/Classes";
    srcFolderName = "0Large_PHIL 102";
    srcFileName   = "L1501291001.xml";
    srcPathImageFolder = QString("%1/%2/").arg(srcPathFolder, "Images");
}


int myCourseXml::printSession()
{
    int iRetval = 0; // default success
    QString outFN = "./session.xml";
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

    forEachQuestion(xmlWriter, this->m_courseList.m_p, srcPathImageFolder, withoutExtension);

    xmlWriter->writeEndElement();   // </QUESTIONS>

    xmlWriter->writeStartElement("STUDENTS");   // <STUDENTS>

    // foreach student
    forEachStudent(xmlWriter, this->m_courseList.m_v);

    xmlWriter->writeEndElement();   // </STUDENTS>

    xmlWriter->writeEndElement();   // </SESSION>

    xmlWriter->writeEndElement();   // </ROOT>

    return iRetval;
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
        xmlWriter->writeAttribute("part", "0.00");
        xmlWriter->writeAttribute("perf", "4.00");
        xmlWriter->writeAttribute("pp", "4.00");
        xmlWriter->writeAttribute("sppp", "4.00");
    }


}

int myCourseXml::writeAggregatesForStudent(QXmlStreamWriter* xmlWriter, const QString sid, const QStringList &list)
{
    xmlWriter->writeAttribute("PossiblePointsPerformance",           "TBD_agr");
    xmlWriter->writeAttribute("StudentPointsPerformancePercentage",  "TBD_agr");
    xmlWriter->writeAttribute("StudentPointsTotalPercentage",        "TBD_agr");
    xmlWriter->writeAttribute("studentperf",                         "TBD_agr");
    xmlWriter->writeAttribute("studentperfpercent",                  "TBD_agr");
}

int myCourseXml::writeStudentAttributes(QXmlStreamWriter* xmlWriter, const QString sid)
{
    xmlWriter->writeAttribute("sid",  sid);
    xmlWriter->writeAttribute("RemoteId",  sid);
    xmlWriter->writeAttribute("name",  "TBD");
    xmlWriter->writeAttribute("ClassAveragePerformancePercentage", "TBD");
}

//const QStringList myCourseXml::helperGetHeaderLabels(const QString list)
//{
//    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
//    QStringList query = list.split(rx);
//    for(int idx = 0; idx < query.length(); idx++)
//    {
//        query[idx].remove('"');
//    }

//    return query;
//}

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

int myCourseXml::forEachStudent(QXmlStreamWriter* xmlWriter, const QStringList &votes)
{
    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QStringList list  = votes; //this->m_courseList.m_v;

    const QStringList labels = myList::helperGetHeaderLabels(votes[0]);
    QStringList coloumns = list[1].split(rx);

    for(int idx = 0; idx < list.length(); )//idx++)
    {
        QString line = list[idx];

        coloumns = line.split(rx);
        QString ss1 = (coloumns.length() == labels.length()) ? coloumns[labels.indexOf("id")] : "null";

        ss1.remove('"');

        xmlWriter->writeStartElement("student");   //<student>
        writeStudentAttributes(xmlWriter, ss1);

        {
            QStringList studentAgregates;  // calc agregates
            writeAggregatesForStudent(xmlWriter, ss1, studentAgregates);
            //writeStudentAggregatesForStudent(sid); // BySession
            //writeSessionAggregatesForSession(thisSession);
        }


        xmlWriter->writeStartElement("qr");   //<qr>
        forEachStudentVote(idx, ss1, list, xmlWriter);
        xmlWriter->writeEndElement();        // </qr>

        xmlWriter->writeEndElement();  // </student>
        qDebug() << "BBBBBBBB________" << idx; // << total;

        qDebug() << "idx = " << idx;
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
        scr.remove('"');
        ans.remove('"');

        if (QString::compare(ss1, student, Qt::CaseInsensitive) != 0) { break; }

        qDebug() << student << ss1 << qid << "ss1 = " << ss1 << "qid = " << qid << "scr = " << scr;


        xmlWriter->writeStartElement("q");   // <q>
        //xmlWriter->writeAttribute("sid",  ss1);
        xmlWriter->writeAttribute("qid",  qid);
        xmlWriter->writeAttribute("scr",  scr);
        xmlWriter->writeAttribute("vote", ans);
        xmlWriter->writeAttribute("response", ans);
        xmlWriter->writeAttribute("icr", "tbd");
        xmlWriter->writeEndElement(); // </q>

    }

}
