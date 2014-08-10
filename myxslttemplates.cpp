#include "myxslttemplates.h"
#include <QTextStream>
#include <QFile>
#include <QResource>
#include <QDebug>

myXsltTemplates::myXsltTemplates()
{

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

    "<xsl:variable name=\"sigChars\" select=\"3\"/>"+ //<!-- <xsl:variable name="sigChars" select="%1"/>-->

    "<xsl:template match=\"ssn/p[@idx='6']\">"+
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
