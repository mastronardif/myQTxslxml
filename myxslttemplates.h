#ifndef MYXSLTTEMPLATES_H
#define MYXSLTTEMPLATES_H

#include <QString>

class myXsltTemplates
{
public:
    myXsltTemplates();
    static int GetManifest(const QString root, QString &out);
    static int         get(const QString root, const QString name, QString &out);

    static QString GetResource000(const QString name);
    static QString GetXSLT_For22(const QString XsltName);
    static QString GetXSLT_For_SignificantCharacters(const QString XsltName);

    static QString removeGetXSLT_For_SignificantCharacters(const QString XsltName);
    static QString GetXSLT_For(const QString name);
};

#endif // MYXSLTTEMPLATES_H
