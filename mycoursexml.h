#ifndef MYCOURSEXML_H
#define MYCOURSEXML_H

#include <QString>
#include <QtXml>
#include "mylist.h"

/// forward class declarations
class myList;

// helper
struct helperMyCourseXmlErr {
    int     iErr;   // 0 default success.
    QString msg;
};

class myCourseXml
{
public:
    myCourseXml(myList &m_courseList);

    //static int printCourse(QStringList list);
    int printSession();

private:
    static int writeTitleElement(QXmlStreamWriter* xmlWriter, const QStringList &session);
    static int writeHdrElement(QXmlStreamWriter* xmlWriter, QStringList ColsToShow);
    static int forEachQuestion(QXmlStreamWriter* xmlWriter, const QStringList &questions, const QString srcPathImageFolder, const QString srcFileName);
    static int forEachStudent (QXmlStreamWriter* xmlWriter, const QStringList &votes);
    static int forEachStudentVote(int &idx, const QString student, const QStringList &list, QXmlStreamWriter* xmlWriter);
    static int writeStudentAttributes(QXmlStreamWriter* xmlWriter, const QString sid);
    static int writeSessionAttributes(QXmlStreamWriter* xmlWriter, const QStringList &session);
    static int writeAggregatesForStudent(QXmlStreamWriter* xmlWriter, const QString sid, const QStringList &list);

    //static  const QStringList helperGetHeaderLabels(const QString list);
private:
    myList m_courseList;
    QString srcPathFolder;
    QString srcPathImageFolder;
    QString srcFolderName;
    QString srcFileName;
};

#endif // MYCOURSEXML_H
