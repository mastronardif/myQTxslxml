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
    forEachStudent(xmlWriter);

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
        if (iCnt == 1) {qDebug() << "BBBBBBBB________" << iCnt << total;}

        query = line.split(rx);
        QString ss1 = (query.length() > 4) ? query[4] : "null";

        if (QString::compare(ss1, lastKnown, Qt::CaseInsensitive) != 0)
        {
            bEnd = true;
            lastKnown = ss1;
            qDebug() << "EEEEEEEE________" << iCnt << total;
            if (iCnt <= total) { qDebug() << "BBBBBBBB________" << iCnt << total; }
        }

        qDebug() << "ss1 = " << ss1;

        if (iCnt == total) {qDebug() << "EEEEEEEE________" << iCnt << total;}

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
