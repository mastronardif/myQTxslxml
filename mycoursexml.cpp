#include "mycoursexml.h"
#include <QFile>
#include <QDebug>
#include <QString>


myCourseXml::myCourseXml(myList &courseList) : m_courseList(courseList)
{
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
    //writeSessionAttributes(QXmlStreamWriter* xmlWriter, const QStringList &session);

    // Questions
    xmlWriter->writeStartElement("QUESTIONS");   // <QUESTIONS>

    forEachQuestion(xmlWriter, this->m_courseList.m_p);

    xmlWriter->writeEndElement();   // </QUESTIONS>

    xmlWriter->writeStartElement("STUDENTS");   // <STUDENTS>

    // foreach student
    forEachStudent(xmlWriter, this->m_courseList.m_v);

    xmlWriter->writeEndElement();   // </STUDENTS>

    xmlWriter->writeEndElement();   // </SESSION>

    xmlWriter->writeEndElement();   // </ROOT>

    return iRetval;
}

int myCourseXml::writeSessionAttributes(QXmlStreamWriter* xmlWriter, const QStringList &session)
{
    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QStringList list  = session;

    const QStringList labels = helperGetHeaderLabels(session[0]);
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
        xmlWriter->writeAttribute("sppp", "TBD");
    }


}
int myCourseXml::writeStudentAttributes(QXmlStreamWriter* xmlWriter, const QString sid)
{
    xmlWriter->writeAttribute("sid",  sid);
    xmlWriter->writeAttribute("RemoteId",  sid);
    xmlWriter->writeAttribute("name",  "TBD");
    xmlWriter->writeAttribute("ClassAveragePerformancePercentage ", "TBD");
}

const QStringList myCourseXml::helperGetHeaderLabels(const QString list)
{
    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QStringList query = list.split(rx);
    for(int idx = 0; idx < query.length(); idx++)
    {
        query[idx].remove('"');
    }

    return query;
}

int myCourseXml::forEachQuestion(QXmlStreamWriter* xmlWriter, const QStringList &questions)
{
    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QStringList list  = questions; //this->m_courseList.m_p;

    const QStringList labels = helperGetHeaderLabels(questions[0]);
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
        xmlWriter->writeAttribute("AveragePercent", "TBD");
        xmlWriter->writeAttribute("CorrectAnswer",   cans);
        xmlWriter->writeEndElement(); // </question>
    }
}

int myCourseXml::forEachStudent(QXmlStreamWriter* xmlWriter, const QStringList &votes)
{
    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QStringList list  = votes; //this->m_courseList.m_v;

    const QStringList labels = helperGetHeaderLabels(votes[0]);
    QStringList coloumns = list[1].split(rx);

    for(int idx = 0; idx < list.length(); )//idx++)
    {
        QString line = list[idx];

        coloumns = line.split(rx);
        QString ss1 = (coloumns.length() == labels.length()) ? coloumns[labels.indexOf("id")] : "null";

        ss1.remove('"');

        xmlWriter->writeStartElement("student");   //<student>
        writeStudentAttributes(xmlWriter, ss1);

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
    const QStringList labels = helperGetHeaderLabels(list[0]);
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
