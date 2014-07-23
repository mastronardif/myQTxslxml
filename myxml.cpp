#include "myxml.h"
#include <QtXmlPatterns/QXmlQuery>
#include <QDebug>

#include <QTextStream>

#include <QtXmlPatterns>
#include <exception>

myxml::myxml()
{
}


QString FindByXpath(QString srcXML, QString xpath);

QString helper_QDomElementToString(QDomElement de)
{
    QString str;
    QTextStream stream(&str);
    de.save(stream, 4);
    //QDomNode node = de.save( //firstChild(); // toText().data(); // documentElement().firstChildElement("child");

    //node.save(stream, 4);
    //qDebug() << "\n holy f in \n" << str << "\n";
    return str;
}

QDomElement helper_xmltoDE(QString xml)
{
    QDomDocument doc("polenumberNine");
    QDomElement deRetval;
    //QDomElement root = doc.firstChildElement("database");
    //QDomElement elt = root.firstChildElement("entry");
    // if ( !doc.setContent( &f ) ) {
//    QDomDocument doc( "mydocument" );
//             QFile f( "mydocument.xml" );
//             if ( !f.open( IO_ReadOnly ) )
//                 return;
//             if ( !doc.setContent( &f ) ) {
//                 f.close();
//                 return;
//             }
//             f.close();

//    QByteArray data(QByteArray::fromRawData(xmlData, sizeof(xmlData)-1));
//    QBuffer buffer(&data);
//    if (buffer.open(QIODevice::ReadOnly)) {

    try
    {
        bool bbb = doc.setContent(xml);
        if (bbb)
        {
            deRetval = doc.documentElement();

            QString str;
            QTextStream stream(&str);
            QDomNode node = doc.documentElement().firstChildElement("child");

            node.save(stream, 4);
            //qDebug() << str;
        }
    }
    catch(int e) //catch by value
        {
        qDebug() << "FM" << "Exception with the number:  " << e << endl;
        }
    catch (const QException& e) //catch by reference
    //...or catch (const exception& e)
        {
        qDebug() << "FM" << e.what() << endl;
        }
    catch (...)
        {
        qDebug() << "FM" << "Unhandled exception";
        }

    return deRetval;
}

//void clsSession__readXmlFile(QString sessionFileName)
//{
//    QFile file = QFile(sessionFileName);
//    QDomDocument xDoc;
//    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        qDebug() << "FM" << "file->open error";
//    }
//    else
//    { xDoc.setContent(file); }

//    file.close();

////    QString xpath;
////    QXmlQuery qq;
////    qq.bindVariable("inputDocument", &device);
////    QString xq = "doc($inputDocument)"+xpath;
////    qq.setQuery(xq);
////    qq.
////    bool rc1 = qq.evaluateTo(&retval);

//}

QString ReadfFileToString(QString fp)
{
    QString retval;
    //const QString file2("C:\\iClicker7\\DBG_myqtxslxm\\debug\\Lq1406110746.xml");
    //QFile fn(file2);
//qDebug() << "\nReadfFileToString  \n" << fp << "\n";
    try
    {
    QFile fn(fp);
    bool ret = fn.open(QIODevice::ReadOnly | QIODevice::Text);
    if( ret )
    {
       QTextStream stream(&fn);
       retval = stream.readAll();
    }

    fn.close();
    }
    catch(int e) //catch by value
        {
        qDebug() << "FM" << "Exception with the number:  " << e << endl;
        }
    catch (const QException& e) //catch by reference
    //...or catch (const exception& e)
        {
        qDebug() << "FM" << e.what() << endl;
        }
    catch (...)
        {
        qDebug() << "FM" << "Unhandled exception";
        }


    return retval;
}




QString FindByXpath00(QString srcFN, QString xp)
{
    //QString xml = ReadfFileToString(srcFN);

    return FindByXpath(srcFN, xp);
}

QString myxml::xsl_xml_FromStringFile(const QString xslt, QString fnxml, QString fout)
{
    qDebug() << xslt;
    QString out;
    QBuffer device;

    device.setData(xslt.toUtf8());
    device.open(QIODevice::ReadOnly);

    QXmlQuery query(QXmlQuery::XSLT20);

    //query.setFocus(QUrl(fnxml));
    query.setFocus(QUrl::fromLocalFile(fnxml));

    query.setQuery(&device);
    query.evaluateTo(&out);
    device.close();
    return out;
}

QString myxml::xsl_xml_FromFiles(const QString fnxsl, QString fnxml, QString fout)
{
    //Find();
    //return "I called find()";
    QString str = QString("\n %1 %2 %3 \n").arg("fnxsl", "fnxml", "fout");
    //myxml::xsl_xml(fnxsl, fnxml, fout);

    qDebug() << str;
    QString out;
    QXmlQuery query(QXmlQuery::XSLT20);
    //QXmlQuery query(QXmlQuery::XQuery10);

    query.setFocus(QUrl(fnxml));
    query.setQuery(QUrl(fnxsl));
    query.evaluateTo(&out);

    return out;
}


QDomElement myxml::Find()
{
    QDomElement retval;
    QString results;
    QString xpath = "/ssn/p[@idx='27']/.";
    results = FindByXpath00("C:\\iClicker7\\DBG_myqtxslxm\\debug\\Lq1406110746.xml", xpath);
    qDebug() << results;

    xpath = "/ssn/p[@idx='28']/.";
   results = FindByXpath00("C:\\iClicker7\\DBG_myqtxslxm\\debug\\Lq1406110746.xml", xpath);
 qDebug() << results;
    return retval;

    QString myQString ="<document idx=\"27\">content</document>";
    const char xmlData[]=
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<plist version=\"1.0\"><dict>"
            "<key>BuildMachineOSBuild</key><string>13A598</string>"
            "<key>CFBundleShortVersionString</key><string>01.4 holy f</string>"
            "<key>CFBundleSignature</key><string>????</string>"
            "<key>CFBundleVersion</key><string>1.4</string>"
            "<key>NSPrincipalClass</key><string>NSApplication</string>"
            "</dict></plist>";

    //QString xpath = "/ssn/p[@idx='27']/<thequestoin qn=\"{@qn}\">{v}</thequestoin>";

    QString xml = ReadfFileToString("C:\\iClicker7\\DBG_myqtxslxm\\debug\\Lq1406110746.xml");

    QBuffer device;

    device.setData(xml.toUtf8());
    device.open(QIODevice::ReadOnly);
    QXmlQuery qq;
    qq.bindVariable("inputDocument", &device);
    QString xq = "doc($inputDocument)"+xpath;
    qq.setQuery(xq);
    //qq.setQuery("doc($inputDocument)/ssn/p[@idx='27']/<thequestoin qn=\"{@qn}\">{v}</thequestoin>");
     QString version1;
    bool rc1 = qq.evaluateTo(&version1);
    qDebug() << rc1 << version1;

return retval;

    QTextStream out(stdout);
     QByteArray data(QByteArray::fromRawData(xmlData, sizeof(xmlData)-1));
     QBuffer buffer(&data);
     if (buffer.open(QIODevice::ReadOnly)) {
         QString version;
         QXmlQuery query;
         query.bindVariable("file", &buffer);
          query.setQuery("doc($kmlFile)/ssn/p[@idx='27']/<thequestoin qn=\"{@qn}\">{v}</thequestoin>");

         query.setQuery("declare variable $file external; doc($file)/plist/dict/key[node()='CFBundleShortVersionString']/following-sibling::string[1]/node()");
         bool rc = query.evaluateTo(&version);
         qDebug() << rc << version;
     }

     //qDebug() << ReadfFileToString("C:\\iClicker7\\DBG_myqtxslxm\\debug\\Lq1406110746.xml");

     QString fnXML = "C:\\iClicker7\\DBG_myqtxslxm\\debug\\Lq1406110746.xml";
     QFile file(fnXML);
     file.open(QIODevice::ReadOnly);

     QXmlQuery query;
     query.bindVariable("kmlFile", &file);
     query.setQuery("doc($kmlFile)/ssn/p[@idx='27']/<thequestoin qn=\"{@qn}\">{v}</thequestoin>");

     QString result;
     query.evaluateTo(&result);

     qDebug() << result;

     file.close();




//    QBuffer device;
//        device.setData(myQString.toUtf8());
//        device.open(QIODevice::ReadOnly);

//        QXmlQuery query;
//        query.bindVariable("inputDocument", &device);
//        query.setQuery("doc($inputDocument)/query[/document/.]");

//            QByteArray outArray;
//                    QBuffer buffer2(&outArray);
//                    buffer.open(QIODevice::ReadWrite);
//                 QXmlFormatter formatter(query, &buffer2);
//              if (!query.evaluateTo(&formatter)) {
//                  qDebug() << "Cannot Execute Query An error occured while executing the query.";

//              }
//              buffer2.close();
//    qDebug() << QString::fromUtf8(outArray.constData());


//xmlpatterns  myquery.xq
//    QFile xq("/Users/frank.mastronardi/Dbg-myqtxslxml/myquery.xq");

//    QXmlQuery query;
//    query.setQuery() (&xq, QUrl::fromLocalFile(xq.fileName()));


//    QByteArray outArray;
//            QBuffer buffer(&outArray);
//            buffer.open(QIODevice::ReadWrite);
//         QXmlFormatter formatter(query, &buffer);
//      if (!query.evaluateTo(&formatter)) {
//          qDebug() << "Cannot Execute Query An error occured while executing the query.";

//      }
//      buffer.close();

////    QString myOutputDevice;
////    query.evaluateTo(&myOutputDevice);
//    qDebug() << QString::fromUtf8(outArray.constData());

    //QXmlSerializer serializer(query, myOutputDevice);
    //query.evaluateTo(&serializer);


    return retval;
}

//QString myxml::xslxml_FromStringFile(QString xsl, QString fnxml, QString fout)
QString myxml::Find(QString xpath, QString fnxml, QString fout)
{
    //QString xpath = "/ssn/p[@idx='27']/.";
    QString results = FindByXpath00(fnxml, xpath);
    return results;
}

QString FindByXpath(QString srcXML, QString xpath)
{
    qDebug() <<  __FILE__ << __LINE__  << __func__;
    // qDebug() << QString("\n%1 %2 %3\n").arg(__func__ , __LINE__, __FILE__);
    QString retval = "";   // Default found nothing.
    QBuffer device;
//qDebug() << srcXML;
//qDebug() << xpath;

    device.setData(srcXML.toUtf8());
    device.open(QIODevice::ReadOnly);
    QXmlQuery qq(QXmlQuery::XSLT20);
    qq.bindVariable("inputDocument", &device);
    QString xq = "doc($inputDocument)"+xpath;
    qq.setQuery(xq);
    bool rc1 = qq.evaluateTo(&retval);

    return retval;
}



QString myxml::xsl_xml(QString fnxsl, QString fnxml, QString fout)
{
    // /Users/frank.mastronardi/fxm/dev/xml/myexcel
    // a2.xml a2.xsl

    fnxsl = "/Users/frank.mastronardi/fxm/dev/xml/myexcel/a2.xsl";
    fnxml = "/Users/frank.mastronardi/fxm/dev/xml/myexcel/a2.xml";
    //fnxsl = "/Users/frank.mastronardi/fxm/dev/xml/myexcel/t1.xsl";
    //fnxml = "/Users/frank.mastronardi/fxm/dev/xml/myexcel/t1.xml";

    QString out;
    //QXmlQuery query(QXmlQuery::XSLT20);
    QXmlQuery query(QXmlQuery::XQuery10);
    //QXmlQuery query(QXmlQuery::XPath20);

    qDebug() << "\n Not working yet W/ Qt xslt processor\n";
//return "";
    query.setFocus(QUrl(fnxml));
    query.setQuery(QUrl(fnxsl));
    query.evaluateTo(&out);
    //webview->setHtml(out);
    qDebug() << "output(" << out << ").";

    QTextStream cin(stdin);
    QTextStream cout(stdout);

    cout << out << endl;


    return "";
}

