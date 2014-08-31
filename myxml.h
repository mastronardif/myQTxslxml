#ifndef MYXML_H
#define MYXML_H
#include <QString>
#include <QDomElement>

QString     helper_QDomElementToString(QDomElement de);
QDomElement helper_xmltoDE(QString xml);

class myxml
{
public:
    myxml();

    static int applyTemplate_xsl_xml_FromFiles(const QString fnxsl, const QString fnxml, QString &dest);
    static int applyTemplate_xsl_xml_FromStringFile(const QString xslt, QString fnxml, QString &dest);

    static  QString Find(QString fnxpath, QString fnxml, QString fout);
    static  QString xsl_xml(QString fnxsl, QString fnxml, QString fout);
    static int FindByXpathFromString(QString srcXML,    QString xpath, QString &parOut);
    static int FindByXpathFromFile(QString srcFileName, QString xpath, QString &parOut);

private:
    static  QDomElement Find();
};

#endif // MYXML_H
