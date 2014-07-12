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


    static  QString Find(QString fnxpath, QString fnxml, QString fout);
    static  QString xsl_xmlFromStrings(const QString fnxsl, QString fnxml, QString fout);
    static  QString xsl_xml22(QString fnxsl, QString fnxml, QString fout);
    static  QString xsl_xml(QString fnxsl, QString fnxml, QString fout);

private:
    static  QDomElement Find();
};

#endif // MYXML_H
