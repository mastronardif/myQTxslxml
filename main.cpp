#include <QCoreApplication>
#include <iostream>
#include <QDebug>
#include <QTime>
#include "myxml.h"
#include "myxslttemplates.h"

using namespace std;

// http://www.dpawson.co.uk/xsl/sect2/identity.html#d5916e13
//xsltproc   myexcelCols.xsl L1406021139.csv
// /Users/frank.mastronardi/Qt5.2.1/5.2.1/clang_64/bin/xmlpatterns -help
// ./myqtxslxml   list01.xsl  di_vidoes.xml
// /Users/frank.mastronardi/Qt5.2.1/5.2.1/clang_64/bin/xmlpatterns  ./list01.xsl  ./di_vidoes.xml
QString ReadfFileToString(QString fp);
int main(int argc, char *argv[])
{
#ifndef FMTIMEANALYSIS
    QTime time;
    time.start();
#endif
    QString fnxml;
    QString fnxsl;
    QCoreApplication a(argc, argv);

    //fnxsl = "/ssn/p[@idx='27']/.";

    //fnxml = "/Users/frank.mastronardi/Dbg-myqtxslxml/Lq1406110746.xml";
    //fnxsl = "C:\\myworkspaces\\myQTxslxml\\runtimeFiles\\SignificantFlowers.xsl";
    fnxsl = "/Users/frank.mastronardi/Dbg-myqtxslxml/SearchReplace03.xsl";
    //fnxsl = "/Users/frank.mastronardi/Dbg-myqtxslxml/test.xsl";
    //fnxml = "C:\\myworkspaces\\myQTxslxml\\runtimeFiles\\sig_L1406270851.xml";
    fnxml = "/Users/frank.mastronardi/Dbg-myqtxslxml/Lq1406110746.xml";

    if (argc>1)
    {
        fnxsl = argv[1];
        if (argc > 2)
                fnxml = argv[2];
    }
        //QString str = QString("\n %1 %2 %3 \n").arg(QString::number(argc), argv[1], argv[2]);

    if (1==1)
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

        QString out = myxml::xsl_xml_FromStringFile(xslt00, fnxml,  "./theoutput.xml" );
        // qDebug() << "\n xsl_xmlFromStrings = " << fnxsl << "in " << fnxml << "\n" << out << "\n";
        std::cout << out.toStdString() << "\n";
    }


if (1==122)
{
    QString out = myxml::xsl_xml_FromFiles(fnxsl, fnxml,  "./theoutput.xml" );
    //std::cout << "\n Find = " << fnxsl << "in " << fnxml << "\n" << out << "\n";
    std::cout << out.toStdString() << "\n";
//return 0;
}

if (1==11)
 {
        QString out = myxml::Find(fnxsl, fnxml,  "./theoutput.xml" );

        qDebug() << "\n Find = " << fnxsl << "in " << fnxml << "\n" << out << "\n";
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


#ifndef FMTIMEANALYSIS
    int difference = time.elapsed();
    QString str = QString("\n[%1] Func(%2) took %3 msec \n").arg(QDateTime::currentDateTime().toString("MM-dd-yy hh:mm:ss.zzz"), __FUNCTION__, QString::number(difference));
    qDebug() << str;
#endif

     return 0; // success
    //return a.exec();
}
