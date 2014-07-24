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
