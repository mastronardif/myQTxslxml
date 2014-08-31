#include "myxslttemplates.h"
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QResource>
#include <QDebug>
#include <QRegularExpression>

#include "myxml.h"

QString ReadfFileToString(QString fp);

myXsltTemplates::myXsltTemplates()
{

}

int myXsltTemplates::Test(const QString rootFilePath, const QString name, QString &out)
{
    int iRetval = 0; // success
    QString fileName;
    QString results;
    QString xslt;

    // find
    iRetval =   myXsltTemplates::get(rootFilePath, name, fileName);
    QString dirPath = QFileInfo(rootFilePath).absolutePath();
    QString path = QDir(dirPath).filePath(fileName);

    // apply
    //GetManifest(mainifest,xslt);
    //myxml::xsl_xml_FromFiles(path, rootFilePath, results);
    xslt = ReadfFileToString(path);
    //iRetval =  myxml::applyTemplate_xsl_xml_FromStringFile(xslt, rootFilePath, results);
    iRetval =  myxml::applyTemplate_xsl_xml_FromFiles(path, rootFilePath, results);

    //myxml::xsl_xml_FromStringFile(xslt, rootFilePath, results);
    // print
    qDebug() << results;
    out=results;
    return iRetval;
}

int myXsltTemplates::get(const QString root, const QString name, QString &out)
{
     int iRetval = 0; // Success

     QString xpath = "/RCC/file[@n='%1']/.";
     xpath = QString(xpath).arg(name);

     //The XQuery actually ran correctly. It selected a bunch of xml:id attributes and put them in the result set.
     //But then xmlpatterns sent the result set to a serializer, which tried to output it as well-formed XML.

     QString fnxml = ReadfFileToString(root);
     QString xml;
     iRetval = myxml::FindByXpathFromString(fnxml,  xpath, xml);

     QRegularExpression re("path=\"([^\"]*)\"");
     QRegularExpressionMatch match = re.match(xml);
     if (match.hasMatch() &&  (match.lastCapturedIndex() == 1) )
     {
        out = match.captured(1);
     }
     else
     {
         iRetval = -401;
     }

     return iRetval;
}

int myXsltTemplates::GetManifest(const QString root, QString &out)
{
    int iRetval = 0; // Success

    //ssn/p[@idx='26']/@isDel
   // QString xpath = "/RCC/file[@idx='26']/."; //"/ssn/p[@idx='15']/.";
    QString xpath = "/RCC/file[@n='SearchReplace03.xsl']/.";
    //return myxml::FindByXpathFromString(root,  xpath, out);
    QString fnxml = ReadfFileToString(root);
    iRetval = myxml::FindByXpathFromString(fnxml,  xpath, out);
    return iRetval;

}

QString myXsltTemplates::GetResource000(const QString name)
{
    QResource common(name);
    //QResource common(":/xsltTemplates/SearchReplace03.xsl");

QFile commonFile(common.absoluteFilePath());

if (!commonFile.open(QIODevice::ReadOnly | QIODevice::Text))
{
    qDebug() << "Unable to open file: " << commonFile.fileName() << " besause of error " << commonFile.errorString() << endl;

    return "";
}

QTextStream in(&commonFile);

QString content = in.readAll();
return content;
}

QString myXsltTemplates::GetXSLT_For22(const QString XsltName)
{
    // sw/ on the name
    QString retval;

    if (XsltName.compare("RemoveClickerQuestion.xslt", Qt::CaseInsensitive) == 0)
    {
//        QString ReadfFileToString(QString fp);
//        return ReadfFileToString("/Users/frank.mastronardi/myQTxslxml/runtimeFiles/Remove_Ids.xsl");

        retval = QString(QString("")+
                         "<?xml version=\"1.0\" encoding=\"utf-8\"?>"+
                         "<xsl:stylesheet version=\"1.0\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\">"+
                         "<xsl:output method=\"xml\" indent=\"yes\"/>"+
                         "<xsl:strip-space elements=\"*\" />\n"+

                         "<xsl:template match=\"@*|node()\">"+
                          "<xsl:copy>"+
                           "<xsl:apply-templates select=\"@*|node()\"/>"+
                          "</xsl:copy>"+
                         "</xsl:template>"+

"<xsl:template match=\"ssn/p/v[@id='#0C0F181B']|ssn/p/v[@id='#276D6923']\"/>"+

                         "</xsl:stylesheet>"+
    ""
    );
    }   // end RemoveClickerQuestion.xslt

    return retval;
}



QString myXsltTemplates::GetXSLT_For(const QString name)
{
    // sw/ on the name
    QString retval;
retval = QString(QString("")+
            "<xsl:stylesheet version=\"1.0\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\">"+
                 "<xsl:template match=\"node()|@*\">"+
                  "<xsl:copy>"+
                   " <xsl:apply-templates select=\"@*|node()\"/>"+
                  "</xsl:copy>"+
                "</xsl:template>"+

                 "<xsl:template match=\"__XP_FIND_Q_BY_IDX__\">"+
                 "<p isDel=\"__ISDEL_ACTION__\">"+
                 "   <xsl:apply-templates select=\"@*|node()\"/>"+
                 "  </p>"+
                 "</xsl:template>"+
            "</xsl:stylesheet>"+
                 ""
            );

    //retval="";
    return retval;
}

QString myXsltTemplates::GetXSLT_For_SignificantCharacters(const QString XsltName)
{
    // sw/ on the name
    QString retval;

    retval = QString(QString("")+
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>"+
    "<xsl:stylesheet version=\"1.0\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\">"+
    "<xsl:output method=\"xml\" indent=\"yes\"/>"+
    "<xsl:strip-space elements=\"*\" />\n"+

    "<xsl:template match=\"@*|node()\">"+
     "<xsl:copy>"+
      "<xsl:apply-templates select=\"@*|node()\"/>"+
     "</xsl:copy>"+
    "</xsl:template>"+

    "<xsl:variable name=\"Qidx\" select=\"%1\"/>"+
    "<xsl:variable name=\"sigChars\" select=\"%2\"/>"+

    "<xsl:template match=\"ssn/p[@idx=$Qidx]\">"+
    "<xsl:call-template name=\"makeSignificant01\" />"+
    "</xsl:template>"+

    "<xsl:template name=\"makeVs\">"+
    //<!-- set I begin -->


    "<xsl:variable name=\"makeVs00\">"+
    "<xsl:for-each select=\"v\">"+
    //<!-- <xsl:copy-of select="." /> -->

    "<xsl:choose>"+
    //<!-- ******************************************************************* -->
            "<xsl:when test=\"name(.) = 'v'\">"+
                //"<!-- <ORIGINAL> <xsl:copy-of select="." /> </ORIGINAL> -->
                "<xsl:element name=\"{name(.)}\">"+

                "<xsl:for-each select=\"./@*\">"+

    "<xsl:choose>"+

                  "<xsl:when test=\"name(.) = 'ansO'\">"+
                    //<!-- Skip we will add at the end -->
                  "</xsl:when>"+

                  "<xsl:when test=\"name(.) = 'ans'\">"+
                    //<!-- Skip we will add at the end -->
                  "</xsl:when>"+

    "<xsl:when test=\"name(.) = 'sig_ans'\">"+
    //<!-- have only one attrib by said name -->
    "</xsl:when>"+

    "<xsl:when test=\"name(.) = 'remove_ans'\">"+
    "<xsl:attribute name=\"{name(.)}\"><xsl:value-of select=\"substring(.,1, $sigChars)\"/> </xsl:attribute>"+
    "<xsl:attribute name=\"sig_{name(.)}\"><xsl:value-of select=\"substring(.,1, $sigChars)\"/> </xsl:attribute>"+
    "</xsl:when>"+

    "<xsl:otherwise>"+
    "<xsl:copy-of select=\".\" />"+
    "</xsl:otherwise>"+
    "</xsl:choose>"+

                "</xsl:for-each>"+


    "<xsl:choose>"+
        "<xsl:when test=\"not(./@ansO)\">"+
            "<xsl:attribute name=\"ansO\"><xsl:value-of select=\"@ans\"/></xsl:attribute>"+
            "<xsl:attribute name=\"ans\"><xsl:value-of select=\"substring(@ans,1, $sigChars)\"/></xsl:attribute>"+
        "</xsl:when>"+
        "<xsl:otherwise>"+ //<!-- unchanged! -->
            "<xsl:attribute name=\"ansO\"><xsl:value-of select=\"@ansO\"/></xsl:attribute>"+
            "<xsl:attribute name=\"ans\"><xsl:value-of select=\"substring(@ansO,1, $sigChars)\"/></xsl:attribute>"+
        "</xsl:otherwise>"+
    "</xsl:choose>"+
                "</xsl:element>"+

            "</xsl:when>"+
            //<!-- ******************************************************************* -->
    "</xsl:choose>"+

    "</xsl:for-each>"+
    "</xsl:variable>"+
    "<xsl:copy-of select=\"$makeVs00\" />"+
    "</xsl:template>"+


    "<xsl:template name=\"makeRespLs\">"
        "<xsl:param name=\"pVotes\"/>"

    "<xsl:variable name=\"makeRespLs00\">"

    //<!-- set I begin -->
     //<!-- <xsl:for-each select="v"> -->
     "<xsl:for-each select=\"$pVotes/v\">"
        "<xsl:sort select =\"upper-case(substring(@ans,1, $sigChars))\"/>"
        "<xsl:choose>"
        "<xsl:when test=\"name(.) = 'v'\">"
        "<row>"

        "<xsl:attribute name=\"sig_{name(.)}\">"
             "<xsl:value-of select =\"upper-case(substring(@ans,1, $sigChars))\"/>"
        "</xsl:attribute>"
        "</row>"

        "</xsl:when>"
        "</xsl:choose>"
     "</xsl:for-each>"
    "</xsl:variable>"


    //<!-- ******************************* -->
    //<!-- ******************************* -->
    //<!-- set II begin -->

    "<xsl:variable name=\"makeRespLs00\">"
     "<xsl:for-each select=\"$makeRespLs00/row\">"

    "<xsl:if test=\"position() = 1\">"
    "<row n=\"set II\">"
    "<xsl:attribute name=\"rs2\"><xsl:value-of select=\"position()\"/></xsl:attribute>"
    "<xsl:attribute name=\"rs20\"><xsl:value-of select=\"'null'\"/></xsl:attribute>"
    "<xsl:attribute name=\"sig_v\"><xsl:value-of select=\"@sig_v\"/></xsl:attribute>"
    "<xsl:attribute name=\"pos\"><xsl:value-of select=\"'first'\"/></xsl:attribute>"
    "</row>"
    "</xsl:if>"

    //<!-- sequence change -->
    "<xsl:if test= \"position() != 1 and @sig_v !=  preceding::row[1]/@sig_v\">"

    "<row n=\"set II an rc\">"
    "<xsl:attribute name=\"rs2\"><xsl:value-of select=\"position()\"/></xsl:attribute>"
    "<xsl:attribute name=\"rs20\"><xsl:value-of select=\"'null'\"/></xsl:attribute>"
    "<xsl:attribute name=\"sig_v\"><xsl:value-of select=\"@sig_v\"/></xsl:attribute>"
    "<xsl:attribute name=\"pos\"><xsl:value-of select=\"'middle'\"/></xsl:attribute>"
    "</row>"

    "</xsl:if>"
    "<xsl:if test=\"position() = last()\">"
        "<row n=\"set II\">"
            "<xsl:attribute name=\"rs2\"><xsl:value-of select=\"position()\"/></xsl:attribute>"
            "<xsl:attribute name=\"rs20\"><xsl:value-of select=\"'null'\"/></xsl:attribute>"
            "<xsl:attribute name=\"sig_v\"><xsl:value-of select=\"@sig_v\"/></xsl:attribute>"
            "<xsl:attribute name=\"pos\"><xsl:value-of select=\"'last'\"/></xsl:attribute>"
        "</row>"

    "</xsl:if>"
    "</xsl:for-each>"
    "</xsl:variable>"

    //<!-- ******************************* -->
    //<!-- ******************************* -->
    //<!-- <xsl:copy-of select="$makeRespLs00"/> -->
    //<!-- end  -->


    //<!-- <fmdebug msg="set III"/> -->
    "<xsl:variable name=\"makeRespLs00\">"
     "<xsl:for-each select=\"$makeRespLs00/row\">"
      "<xsl:choose>"

      //<!-- sequence change -->

      "<xsl:when test= \"position() =  last()\">"
    "<respR>"
    "<xsl:attribute name=\"respS\">"
    "<xsl:value-of select=\"preceding::row[1]/@sig_v\" />"
    "</xsl:attribute>"

    "<xsl:attribute name=\"respLS\"><xsl:value-of select=\"lower-case(preceding::row[1]/@sig_v)\"/></xsl:attribute>"

    "<xsl:attribute name=\"respCP\">"
    "<xsl:value-of select=\"concat(1+(@rs2)-preceding::row[1]/@rs2, ',', '0.00')\"/>"
    "</xsl:attribute>"
    "</respR>"

    "<xsl:if test=\"@sig_v !=  preceding::row[1]/@sig_v\">"
    "<row v=\"difPrec\">"
    "<xsl:attribute name=\"b4_sig_v\">"
    "<xsl:value-of select=\"preceding::row[1]/@sig_v\" />"
    "</xsl:attribute>"
    "</row>"

    "</xsl:if>"
    "</xsl:when>"

      "<xsl:when test= \"@sig_v !=  preceding::row[1]/@sig_v\">"
    "<respR>"
    "<xsl:attribute name=\"respS\">"
    "<xsl:value-of select=\"preceding::row[1]/@sig_v\" />"
    "</xsl:attribute>"

    "<xsl:attribute name=\"respLS\"><xsl:value-of select=\"lower-case(preceding::row[1]/@sig_v)\"/></xsl:attribute>"

    "<xsl:attribute name=\"respCP\">"

    "<xsl:value-of select=\"concat((@rs2)-preceding::row[1]/@rs2, ',', '0.00')\"/>"
    "</xsl:attribute>"
    "</respR>"

    "</xsl:when>"

      "</xsl:choose>"
    "</xsl:for-each>"
    "</xsl:variable>"
    //<!-- end  -->


     //<!-- <xsl:copy-of select="$makeRespLs00"/>-->
    "<respLs>"
    "<xsl:attribute name=\"b4_sigChars\"><xsl:value-of select=\"$sigChars\" /></xsl:attribute>"
    "<xsl:attribute name=\"b4_Qidx\"><xsl:value-of select=\"$Qidx\" /></xsl:attribute>"

    "<xsl:copy-of select=\"$makeRespLs00\"/>"
    "</respLs>"

    //<!-- </makeRespLs> -->
    "</xsl:template>"

    "<xsl:template name=\"makeSignificant01\">"

     "<makeSignificant01>"
        //<!-- <Original><xsl:copy-of select="." /></Original>-->

    "<xsl:element name=\"{name(.)}\">"
        "<xsl:for-each select=\"./@*\">"
        "<xsl:choose>"
            "<xsl:when test=\"name(.) = 'sig'\">"
                "<xsl:attribute name=\"{name(.)}\"><xsl:value-of select=\"$sigChars\"/></xsl:attribute>"
            "</xsl:when>"
                "<xsl:otherwise>"
                    "<xsl:attribute name=\"{name(.)}\"><xsl:value-of select=\".\"/></xsl:attribute>"
                "</xsl:otherwise>"
        "</xsl:choose>"
        "</xsl:for-each>"


        //<!-- for each element -->
        "<xsl:for-each select=\"./*\">"

            "<xsl:choose>"
                  //<!-- <xsl:when test="@respLS">-->
                  "<xsl:when test=\"name(.) = 'respLs'\">"
    //<!-- Skip we will add at the end -->
            "</xsl:when>"

            //<!-- ******************************************************************* -->
            //<!-- ******************************************************************* -->

    "<xsl:when test=\"name(.) = 'v'\">"
    //<!-- <IGNORE_v/> -->
    "</xsl:when>"
                     //<!-- Ignore other emlements -->
                     "<xsl:otherwise>"
                        "<xsl:copy-of select=\".\" />"
                     "</xsl:otherwise>"
             "</xsl:choose>"
        "</xsl:for-each>"

    "<xsl:variable name=\"theVs\">"
        "<xsl:call-template name=\"makeVs\"/>"
    "</xsl:variable>"

     "<xsl:copy-of select=\"$theVs\" />"

        "<xsl:call-template name=\"makeRespLs\">"
            "<xsl:with-param name=\"pVotes\" select=\"$theVs\"/>"
        "</xsl:call-template>"

    "</xsl:element>"
    "</makeSignificant01>"

    "</xsl:template>"




    "</xsl:stylesheet>"+
    ""
    );

    return retval;

}

QString myXsltTemplates::removeGetXSLT_For_SignificantCharacters(const QString XsltName)
{
    // sw/ on the name
    QString retval;

    retval = QString(QString("")+
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>"+
    "<xsl:stylesheet version=\"1.0\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\">"+
    "<xsl:output method=\"xml\" indent=\"yes\"/>"+
    "<xsl:strip-space elements=\"*\" />\n"+

    "<xsl:template match=\"@*|node()\">"+
     "<xsl:copy>"+
      "<xsl:apply-templates select=\"@*|node()\"/>"+
     "</xsl:copy>"+
    "</xsl:template>"+

    "<xsl:variable name=\"sigChars\" select=\"%1\"/>"+ //<!-- <xsl:variable name=\"sigChars\" select=\"3\"/> <xsl:variable name="sigChars" select="%1"/>-->

    "<xsl:template match=\"ssn/p[@idx='%2']\">"+
        "<xsl:call-template name=\"makeSignificant01\" />"+
    "</xsl:template>"+

    "<xsl:template name=\"makeSignificant01\">"+

     "<makeSignificant01>"+
        "<Original><xsl:copy-of select=\".\" /></Original>"+

    "<newsh_t>"+
    "<xsl:element name=\"{name(.)}\">"+
        "<xsl:for-each select=\"./@*\">"+
        "<xsl:choose>"+
            "<xsl:when test=\"name(.) = 'sig'\">"+
                "<xsl:attribute name=\"{name(.)}\"><xsl:value-of select=\"$sigChars\"/></xsl:attribute>"+
            "</xsl:when>"+

                                "<xsl:otherwise>"+
                                "<xsl:attribute name=\"{name(.)}\">"+
                                    "<xsl:value-of select=\".\"/>"+
                                "</xsl:attribute>"+
                                "</xsl:otherwise>"+
        "</xsl:choose>"+
        "</xsl:for-each>"+


        //"<!-- for each element -->"+
        "<xsl:for-each select=\"./*\">"+

            "<xsl:choose>"+
                  //<!-- <xsl:when test=\"@respLS\">-->
                  "<xsl:when test=\"name(.) = 'respLs'\">"+
                    "<xsl:element name=\"{name(.)}\">"+ // <!-- respLs -->
                           "<xsl:for-each select=\"./@*\">"+

                                "<xsl:attribute name=\"{name(.)}\">"+
                                    "<xsl:value-of select=\".\"/>"+
                                "</xsl:attribute>"+
                            "</xsl:for-each>"+

                            //<!-- elements -->
                            "<xsl:for-each select=\"./*\">"+

                            "<xsl:choose>"+

                                "<xsl:when test=\"name(.) = 'respR'\">"+
                                   //<!-- <xsl:copy-of select=\".\" /> -->
                                    "<xsl:element name=\"{name(.)}\">"+
                                        //<!-- add new attrib or update -->

                                        "<xsl:for-each select=\"./@*\">"+
                                            //<!-- <xsl:attribute name=\"{name(.)}\">
                                            //"<xsl:value-of select=\".\"/>"+ // </xsl:attribute> -->


    "<xsl:choose>"+
    "<xsl:when test=\"name(.) = 'respLS'\">"+
    "<xsl:attribute name=\"{name(.)}\"><xsl:value-of select=\".\"/> </xsl:attribute>"+
    "<xsl:attribute name=\"sig_respLS\"><xsl:value-of select=\"substring(.,1, $sigChars)\"/> </xsl:attribute>"+


    "</xsl:when>"+
                                "<xsl:otherwise>"+ //<!-- leave attributes unchanged -->
                                   "<xsl:copy-of select=\".\" />"+
                                   "<xsl:attribute name=\"{name(.)}\"><xsl:value-of select=\".\"/> </xsl:attribute>"+

                                "</xsl:otherwise>"+
                            "</xsl:choose>"+

                                        "</xsl:for-each>"+

                                   "</xsl:element>"+

                                "</xsl:when>"+


                                //<!-- other elements ignore -->
                                "<xsl:otherwise>"+
                                   "<xsl:copy-of select=\".\" />"+
                                "</xsl:otherwise>"+
                            "</xsl:choose>"+

                            "</xsl:for-each>"+

                        "</xsl:element>"+ // <!-- /respLs -->
                  "</xsl:when>"+



                  "<xsl:when test=\"name(.) = 'v'\">"+
       "<original1/> <xsl:copy-of select=\".\" /> <_original2/>"+

                        "<xsl:element name=\"{name(.)}DUCK\">"+
                        "<xsl:for-each select=\"./@*\">"+

    "<xsl:choose>"+
    "<xsl:when test=\"name(.) = 'sig_ans'\">"+
        //<!-- have only one attrib by said name -->
    "</xsl:when>"+
    "<xsl:when test=\"name(.) = 'ans'\">"+
       "<xsl:attribute name=\"sig_{name(.)}\"><xsl:value-of select=\"substring(.,1, $sigChars)\"/> </xsl:attribute>"+
    "</xsl:when>"+

    "<xsl:otherwise>"+
       "<xsl:copy-of select=\".\" />"+
    "</xsl:otherwise>"+
    "</xsl:choose>"+

                        "</xsl:for-each>"+
                        "</xsl:element>"+
                  "</xsl:when>"+

                     //<!-- Ignore other emlements -->
                     "<xsl:otherwise>"+
                        "<xsl:copy-of select=\".\" />"+
                     "</xsl:otherwise>"+
             "</xsl:choose>"+
        "</xsl:for-each>"+
    "</xsl:element>"+
    "</newsh_t>"+
    "</makeSignificant01>"+

    "</xsl:template>"+
    "</xsl:stylesheet>"+
    ""
    );

    return retval;
}
