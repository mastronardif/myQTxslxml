#ifndef MYXSLTTEMPLATES_H
#define MYXSLTTEMPLATES_H

#include <QString>

class myXsltTemplates
{
public:
    myXsltTemplates();
    static int getManifest(const QString rootFilePath, QString &out);
    static int getFilePath(const QString rootFilePath, const QString name, QString &out);

    static QString GetResource000(const QString name);
    static QString GetXSLT_For22(const QString XsltName);
    static QString GetXSLT_For_SignificantCharacters(const QString XsltName);

    static QString removeGetXSLT_For_SignificantCharacters(const QString XsltName);
    static QString GetXSLT_For(const QString name);

    // test
    static int Test(const QString rootFilePath, const QString name, QString &out);

};

#endif // MYXSLTTEMPLATES_H
