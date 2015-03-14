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

    xmlWriter->writeStartElement("STUDENTS");   // <STUDENTS>

    // foreach student
    forEachStudent00(xmlWriter, this->m_courseList.m_v);
    //forEachStudent(xmlWriter);

    xmlWriter->writeEndElement();   // </STUDENTS>

    xmlWriter->writeEndElement();   // </SESSION>


    xmlWriter->writeEndElement();   // </ROOT>


    return iRetval;
}

int myCourseXml::forEachStudent(QXmlStreamWriter* xmlWriter /* m_v.csv */)
{
    //xmlWriter->writeStartElement("STUDENTS");   // <STUDENTS>

    // foreach student

    QRegExp rx3("(BEGIN|END)");
    rx3.setMinimal(true);
    rx3.setCaseSensitivity(Qt::CaseInsensitive);

    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    bool bEnd = false;
    QStringList list  = this->m_courseList.m_v;
    int total = list.count();
    QStringList query = list[0].split(rx);
    QString lastKnown = (query.length() > 4) ? query[4] : "null";

    int iCnt = 1;
    foreach (const QString &line, list)
    {
        if (iCnt == 1)
        {
            xmlWriter->writeStartElement("student");   // <student>
            qDebug() << "BBBBBBBB________" << iCnt << total;
        }

        query = line.split(rx);
        QString ss1 = (query.length() > 4) ? query[4] : "null";

        if (QString::compare(ss1, lastKnown, Qt::CaseInsensitive) != 0)
        {
            bEnd = true;
            lastKnown = ss1;
            xmlWriter->writeEndElement();   // </student>
            qDebug() << "EEEEEEEE________" << iCnt << total;
            if (iCnt <= total)
            {
                xmlWriter->writeStartElement("student");   // <student>
                qDebug() << "BBBBBBBB________" << iCnt << total;
            }
        }

        QString cleanSs1 = ss1.remove('"');
        xmlWriter->writeAttribute("sid",  ss1);
        qDebug() << "ss1 = " << ss1;



        if (iCnt == total)
        {
            xmlWriter->writeEndElement();   // </student>
            qDebug() << "EEEEEEEE________" << iCnt << total;
        }

        iCnt++;
    }

    xmlWriter->writeStartElement("student");   // <student>

    xmlWriter->writeAttribute("ClassAveragePerformancePercentage",  "Calc");

    xmlWriter->writeAttribute("RemoteId",  "rrr");
    xmlWriter->writeAttribute("StudentId", "sid");

    xmlWriter->writeEndElement();

    // foreach qr
    // forEachQr
    xmlWriter->writeEndElement();   // </student>

    //xmlWriter->writeEndElement();   // </STUDENTS>
}

int myCourseXml::writeStudentAttributes(QXmlStreamWriter* xmlWriter, const QString sid)
{
    xmlWriter->writeAttribute("sid",  sid);
    xmlWriter->writeAttribute("RemoteId",  sid);
    xmlWriter->writeAttribute("name",  "TBD");
    xmlWriter->writeAttribute("ClassAveragePerformancePercentage ", "TBD");
}

const QStringList myCourseXml::helperGetHeaderLabels(QStringList &list)
{
    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QStringList query = list[0].split(rx);
    for(int idx = 0; idx < query.length(); idx++)
    {
        query[idx].remove('"');
    }

    return query;
}

int myCourseXml::forEachStudent00(QXmlStreamWriter* xmlWriter, const QStringList &votes)
{
    //xmlWriter->writeStartElement("STUDENTS");   // <STUDENTS>

    // foreach student

    QRegExp rx3("(BEGIN|END)");
    rx3.setMinimal(true);
    rx3.setCaseSensitivity(Qt::CaseInsensitive);

    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    bool bEnd = false;
    QStringList list  = votes; //this->m_courseList.m_v;
    int total = list.count();
    QStringList coloumns = list[0].split(rx);
    QString lastKnown = (coloumns.length() > 4) ? coloumns[4] : "null";

    const QStringList labels = helperGetHeaderLabels(list);
    //helperGetHeaderLabels(votes);
    //int index= labels["sid"];
    QString ddd = list[1]; //.[labels.indexOf("id")];
    coloumns = list[1].split(rx);

    QString lastKnown22 = (coloumns.length() == labels.length()) ? coloumns[labels.indexOf("id")] : "null";

    int iCnt = 1;
    //foreach (const QString &line, list)
    for(int idx = 0; idx < list.length(); )//idx++)
    {
        QString line = list[idx];

        coloumns = line.split(rx);
        QString ss1 = (coloumns.length() == labels.length()) ? coloumns[labels.indexOf("id")] : "null";

        //QString ss1 = (coloumns.length() > 4) ? coloumns[4] : "null";
        ss1.remove('"');
        //if (iCnt == 1)
        {
            writeStudentAttributes(xmlWriter, ss1);

            xmlWriter->writeStartElement("qr");   // <student>
            forEachStudentVote(idx, ss1, list, xmlWriter);
            xmlWriter->writeEndElement();   // </student>

            xmlWriter->writeEndElement();   // </student>
            qDebug() << "BBBBBBBB________" << iCnt << total;
        }

        qDebug() << "idx = " << idx;
    }

    xmlWriter->writeStartElement("student");   // <student>

    xmlWriter->writeAttribute("ClassAveragePerformancePercentage",  "Calc");

    xmlWriter->writeAttribute("RemoteId",  "rrr");
    xmlWriter->writeAttribute("StudentId", "sid");

    xmlWriter->writeEndElement();

    // foreach qr
    // forEachQr
    xmlWriter->writeEndElement();   // </student>

    //xmlWriter->writeEndElement();   // </STUDENTS>
}

int myCourseXml::forEachStudentVote(int &idx, const QString argStudent, const QStringList &list, QXmlStreamWriter* xmlWriter)
{
    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QString clean;
    QString student = argStudent;
    student.remove('"');

    for(; idx < list.length(); idx++)
    {
        QString line = list[idx];

        QStringList query = line.split(rx);
        QString ss1 = (query.length() > 3) ? query[4]  : "null";
        QString qid = (query.length() > 9) ? query[10] : "null";
        QString scr = (query.length() > 5) ? query[6]  : "null";
        QString ans = (query.length() > 8) ? query[9]  : "null";

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
        xmlWriter->writeEndElement();

    }

}
