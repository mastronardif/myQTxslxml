#include "mycoursexml.h"
#include <QFile>
#include <QDebug>


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

int myCourseXml::forEachStudent(QXmlStreamWriter* xmlWriter)
{
    //xmlWriter->writeStartElement("STUDENTS");   // <STUDENTS>

    // foreach student
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
