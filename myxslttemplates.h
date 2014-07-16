#ifndef MYXSLTTEMPLATES_H
#define MYXSLTTEMPLATES_H

#include <QString>

class myXsltTemplates
{
public:
    myXsltTemplates();

    static QString GetResource000(const QString name);
    static QString GetXSLT_For(const QString name);
};

#endif // MYXSLTTEMPLATES_H
