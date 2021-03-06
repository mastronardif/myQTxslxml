#include <QCoreApplication>
#include <iostream>
#include <QDebug>
#include <QTime>
#include "myxml.h"
#include "myxslt.h"
#include "myxslttemplates.h"
#include "mylist.h"
#include "mycoursexml.h"

using namespace std;

#define FMTIMEANALYSIS
// http://www.dpawson.co.uk/xsl/sect2/identity.html#d5916e13
//xsltproc   myexcelCols.xsl L1406021139.csv
// /Users/frank.mastronardi/Qt5.2.1/5.2.1/clang_64/bin/xmlpatterns -help
// ./myqtxslxml   list01.xsl  di_vidoes.xml
// /Users/frank.mastronardi/Qt5.2.1/5.2.1/clang_64/bin/xmlpatterns  ./list01.xsl  ./di_vidoes.xml
QString ReadfFileToString(QString fp);

QString theRoot = "%1/runtimeFiles/manifest.xml";
//QString theRoot = "C:\\myworkspaces\\Dbg-myqtxslxml\\debug\\runtimeFiles\\mainifest.xml"; //Lq1406110746.xml";


int main(int argc, char *argv[])
{
    int iRetval = 0;
#ifdef FMTIMEANALYSIS
    QTime time;
    time.start();
#endif
    QString fnxml;
    QString fnxsl;
    QString fnOut;
    QCoreApplication a(argc, argv);

    qDebug() << QCoreApplication::applicationDirPath();
    qDebug() << a.applicationFilePath();
    theRoot = QString(theRoot).arg(a.applicationDirPath());
    qDebug() << "theRoot= " << theRoot;
    //fnxsl = "/ssn/p[@idx='27']/.";

  QString srcPathFolder = "/Users/frank.mastronardi/workspace/iclicker741Sources/Debug/Classes/0Large_PHIL 102";
  QString xmlFN = "L1501291001.xml";

//  QString srcPathFolder = "/Users/frank.mastronardi/workspace/iclicker740Sources/Debug/Classes/CH102-1 S2015";
//  QString xmlFN = "L1502040749.xml";

//  QString srcPathFolder = "/Users/frank.mastronardi/workspace/iclicker740Sources/Debug/Classes/test_deleteQ001";
//  QString         xmlFN = "L1504291321.xml";

//  QString         xmlFN = "L1505011353.xml";
//  QString srcPathFolder = "/Users/frank.mastronardi/workspace/iclicker740Sources/Debug/Classes/iclicker-REEF integration Test 4";

//  QString         xmlFN = "L1505151448.xml";
//  QString srcPathFolder = "/Users/frank.mastronardi/workspace/iclicker741Sources/Debug/Classes/icl_2841_case2";

//  QString         xmlFN = "L1505221112.xml";
//  QString srcPathFolder = "/Users/frank.mastronardi/workspace/iclicker741Sources/Debug/Classes/icl_2841big";
//  QString         xmlFN = "L1504150746.xml";
//  QString srcPathFolder = "/Users/frank.mastronardi/workspace/iclicker741Sources/Debug/Classes/CH102-1 S2015";
///Users/frank.mastronardi/workspace/iclicker741Sources/Debug/Classes/CH102-1 S2015/SessionData/L1504150746.xml

  //QString srcPathFolder = "/Users/frank.mastronardi/workspace/iclicker740Sources/Debug/Classes/iclicker-REEF integration Test 3";
    //QString srcPathFolder = "/Users/frank.mastronardi/workspace/iclicker740Sources/Debug/Classes/CH102-1 S2015";
    //QString xmlFN = "L1502090752.xml";

    //QString xmlFN = "L1504031332.xml";  // very large test file.


  //fnxml = "/Users/frank.mastronardi/myQTxslxml/runtimeFiles/"+xmlFN;
    //fnxml= "/Users/frank.mastronardi/workspace/iclicker740Sources/Debug/Classes/iclicker-REEF integration Test 3/SessionData/L1504281548.xml";
    fnxml= QString("%1/SessionData/%2").arg(srcPathFolder, xmlFN);

    fnOut = QString("%1.%2.xml").arg(fnxml, "POC");

    //fnxsl = "C:\\myworkspaces\\myQTxslxml\\runtimeFiles\\xml2csv101.xsl";
    fnxsl = "/Users/frank.mastronardi/myQTxslxml/runtimeFiles/listxml2csv101.xsl";
    //fnxsl = "/Users/frank.mastronardi/Dbg-myqtxslxml/test.xsl";

    //fnxml = "/Users/frank.mastronardi/Dbg-myqtxslxml/Lq1406110746.xml";
    //if (myXsltTemplates::getFilePath(theRoot, "LargeSet01.xml", fnxml) != 0)
    //{
    //    fnxml = "C:\\myworkspaces\\myQTxslxml\\runtimeFiles\\sig_L1406270851.xml";
    //}

    if (argc>1)
    {
        //fnxsl = argv[1];
        if (argc > 2)
        {
                xmlFN = argv[2];
                fnxml = argv[2];
                fnxml.remove('"');
                fnOut = QString("%1.%2.xml").arg(fnxml, "POC");
                if (argc > 3)
                {
                        srcPathFolder = argv[3];
                        srcPathFolder.remove('"');

                        QString path = QString("%1/SessionData/%2").arg(srcPathFolder, fnxml);
                        qDebug() << "xml file path = " << path;
                        fnxml = path;
                }
        }
    }
        //QString str = QString("\n %1 %2 %3 \n").arg(QString::number(argc), argv[1], argv[2]);

    if (1==1)
    {
        QString results;
        QString xslt00 = ReadfFileToString(fnxsl);
        QString xml00  = ReadfFileToString(fnxml);

        QString out;

        // use xml lib version.
        {
            QString fnOut = "./wtf.csv";
            extern int my_xslt_main(const char *fnXslt, const char *theParamsArg, const char *fnSrcXml, const char *fnOut);
            iRetval = my_xslt_main(fnxsl.toStdString().c_str(),
                                   "", fnxml.toStdString().c_str(),
                                   fnOut.toStdString().c_str());

            if (0 == iRetval)
            {
                out = ReadfFileToString(fnOut);
                std::cout << out.toStdString() << "\n";
            }
            //return 123;
        }
        //iRetval = myxml::applyTemplate_xsl_xml_FromStrings(xslt00, xml00, out);
         //iRetval = myxml::applyTemplate_xsl_xml_FromStringFile(xslt00, fnxml, out);
         //iRetval = myxml::applyTemplate_xsl_xml_FromStrings(xslt00, out, out);
        if(iRetval == 0)
        {
            //std::cout << "YY" << out.toStdString() << "ZZ\n"; return 1;

            // list to csv memory thing.
            myList  theCourse;
            S_CourseEntities courseInfo;
            courseInfo.srcPathFolder         =  srcPathFolder; //"/Users/frank.mastronardi/workspace/iclicker740Sources/Debug/Classes/0Large_PHIL 102";
            courseInfo.m_srcPathRemoteIds    =  courseInfo.srcPathFolder + "/SessionData/" + "RemoteID.csv";
            courseInfo.m_srcPathStudentNames =  courseInfo.srcPathFolder + "/gb_export.csv";

            // check for gb or roster.txt
            //QFile file(courseInfo.srcPathFolder + "/roster.txt");
            QFile file;

//            //file.open(QIODevice::ReadOnly | QIODevice::Text);
//            if (file.exists())
//            {
//                courseInfo.m_srcPathStudentNames =  courseInfo.srcPathFolder + "/roster.txt";
//            }

//            file.setFileName(courseInfo.srcPathFolder + "/roster.txt");
//            if (file.exists())
//            {
//                courseInfo.m_srcPathStudentNames =  courseInfo.srcPathFolder + "/roster.txt";
//            }

            QStringList listRosters;
            listRosters << courseInfo.srcPathFolder + "/roster.txt";
            listRosters << courseInfo.srcPathFolder + "/gb_export.csv";
            foreach (QString roster, listRosters)
            {
                file.setFileName(roster);
                if (file.exists())
                {
                    courseInfo.m_srcPathStudentNames =  roster;
                }
            }


//            QFile file2(courseInfo.srcPathFolder + "/gb_export.csv");
//            if (file2.exists())
//            {
//                courseInfo.m_srcPathStudentNames =  courseInfo.srcPathFolder + "/gb_export.csv";
//            }

            courseInfo.srcFileName = xmlFN;

            theCourse.m_courseEntities = courseInfo;

            iRetval = theCourse.makeList(courseInfo, out);
            //myList::printList(theCourse.m_v); // m_course);

            myCourseXml theCourseXml(theCourse);

            iRetval =  theCourseXml.printSession(fnOut);
            qDebug() << "file OUT: " << fnOut;

            QString reportxmlFN = QString("%1/Reports/%2.POC.xml").arg(courseInfo.srcPathFolder, courseInfo.srcFileName);
            qDebug() << "courseInfo: ";
            qDebug() << courseInfo.srcPathFolder;
            qDebug() << reportxmlFN;
        }

        //qDebug() << fnxsl << fnxml;
        //std::cout << xslt00.toStdString() << "\n";
        //std::cout << xml00.toStdString() << "\n";

        //return 0;
//sleep(1);
    }

    if (1==167)
    {
    QString path;
   //iRetval =  myXsltTemplates::GetManifest(theRoot, out);
   //iRetval =   myXsltTemplates::getFilePath(theRoot, "xml2csv101.xsl", path);
   //getFilePath//
    if (0 == iRetval)
    {
        QString results;
        QString xslt00 = ReadfFileToString(path);
        iRetval =  myxml::applyTemplate_xsl_xml_FromStringFile(xslt00, fnxml, results);
        std::cout << results.toStdString() << "\n";
        qDebug() << "___________";
        iRetval =  myxml::applyTemplate_xsl_xml_FromFiles     (path, fnxml, results);
        qDebug() << "_z_z_z_z_z_z_z_z_z_z_";
        //iRetval =  myxml::applyTemplate_xsl_xml_FromFiles(path, fnxml, results);
        std::cout << results.toStdString() << "\n";
    }
//   qDebug() << "get"<<iRetval<<"out("<<out<< ")";
//   myXsltTemplates::Test(theRoot, "ListManifest.xslt", out);
//   qDebug() << "___________"<<out;
//   std::cout << out.toStdString() << "\n";

    //return iRetval;
}
    if (1==101)
    {
         //QString xslt = myXsltTemplates::GetResource000(":/xsltTemplates/MarkQuestion.xslt");
         //QString xslt = myXsltTemplates::GetXSLT_For("MarkQuestion.xslt");
         //qDebug() << xslt;
         //return 123;
         //
//         xslt = xslt.replace("__XP_FIND_Q_BY_IDX__", "ssn/p[@idx='26']");
//         xslt = xslt.replace("__ISDEL_ACTION__",     "FM-Y2");

//         qDebug() << xslt;
        QString xslt00;
        //xslt00 = myXsltTemplates::GetXSLT_For22("RemoveClickerQuestion.xslt");


        QString qIdx = "3";
        QString sigchars = "2";
        //xslt00 = QString(xslt00).arg(sigchars, qIdx);
        //xslt00 = ReadfFileToString(fnxsl);
        //xslt00 = myXsltTemplates::GetXSLT_For_SignificantCharacters("SignificantCharacters.xslt");
        //xslt00 = QString(xslt00).arg(qIdx, sigchars);

        int WriteStringToFile(const QString src, QString fp);
        WriteStringToFile(xslt00, "/Users/frank.mastronardi/myQTxslxml/runtimeFiles/L001.xsl.xml");
        xslt00 = ReadfFileToString(fnxsl);
        //WriteStringToFile(xslt00, "/Users/frank.mastronardi/myQTxslxml/runtimeFiles/r001.xml");
        QString out;
        iRetval = myxml::applyTemplate_xsl_xml_FromStringFile(xslt00, fnxml,  out);
        // qDebug() << "\n xsl_xmlFromStrings = " << fnxsl << "in " << fnxml << "\n" << out << "\n";
        std::cout << out.toStdString() << "\n";
    }


if (1==122)
{
    //QString out = myxml::xsl_xml_FromFiles(fnxsl, fnxml,  "./theoutput.xml" );
    //std::cout << "\n Find = " << fnxsl << "in " << fnxml << "\n" << out << "\n";
    //std::cout << out.toStdString() << "\n";
//return 0;
}

if (1==91)
 {
     QString out;
    //iRetval =  myXsltTemplates::GetManifest(theRoot, out);
    //iRetval =   myXsltTemplates::get(theRoot, "SignificantFlowers.xslt", out);

    qDebug() << "get"<<iRetval<<"out("<<out<< ")";
    myXsltTemplates::Test(theRoot, "ListManifest.xslt", out);
    qDebug() << "___________"<<out;
    std::cout << out.toStdString() << "\n";
    return iRetval;


        QString xpath = "/ssn/p[@idx='15']/.";
        fnxml = "/Users/frank.mastronardi/myQTxslxml/runtimeFiles/Lq1406110746.xml";
        iRetval = myxml::FindByXpathFromFile(fnxml,  xpath, out);

        qDebug() << "************** FindByXpathFromFile **********************";
qDebug() << iRetval << "out = " << out;
qDebug() << "************************************";

qDebug() << "*************** FindByXpathFromString *********************";
xpath = "/ssn/p[@idx='14']/.";
out="";
fnxml = ReadfFileToString(fnxml);
iRetval = myxml::FindByXpathFromString(fnxml,  xpath, out);
qDebug() << iRetval << "out = " << out;
qDebug() << "************************************";


        fnxml = ReadfFileToString(fnxml);
        //myxml::Find();

        out = myxml::Find(xpath, fnxml,  "./theoutput.xml" );

        //
        QString FindByXpath(QString srcXML, QString xpath);
        QString results = FindByXpath(fnxml, xpath);
        qDebug() << "results = " << results;

        //qDebug() << "\n Find = " << fnxsl << "in " << fnxml << "\n" << out << "\n";
        qDebug() << "\n__________________________\n";
        qDebug() << "\n__________________________\n" << "\n"
                    ;
        QDomElement helper_xmltoDE(QString xml);
        QDomElement de = helper_xmltoDE(out);

        out = helper_QDomElementToString(de);
        qDebug() << "\n QDomElement = de  \n" << out << "\n";
        qDebug() << "\n__________________________\n";
        qDebug() << "\n__________________________\n" << "\n";
}
//        {
//            QString str;
//            QTextStream stream(&str);
//            de.save(stream, 4);
//            //QDomNode node = de.save( //firstChild(); // toText().data(); // documentElement().firstChildElement("child");

//            //node.save(stream, 4);
//            qDebug() << "\n holy f in \n" << str << "\n";
//        }

        //qDebug() << "\n\n_____________\n"  << out;

        //QTextStream cin(stdin);
        //QTextStream cout(stdout);
        //cout << out << endl;
    //}
//    qDebug() << "\nUsage: exe xsl  xml";


#ifdef FMTIMEANALYSIS
    int difference = time.elapsed();
    QString str = QString("\n[%1] Func(%2) took %3 msec \n").arg(QDateTime::currentDateTime().toString("MM-dd-yy hh:mm:ss.zzz"), __FUNCTION__, QString::number(difference));
    qDebug() << str;
#endif

     return 0; // success
    //return a.exec();
}
