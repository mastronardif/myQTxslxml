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
