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
    static int forEachQuestion(QXmlStreamWriter* xmlWriter, const QStringList &questions);
    static int forEachStudent (QXmlStreamWriter* xmlWriter, const QStringList &votes);
    static int forEachStudentVote(int &idx, const QString student, const QStringList &list, QXmlStreamWriter* xmlWriter);
    static int writeStudentAttributes(QXmlStreamWriter* xmlWriter, const QString sid);
    static int writeSessionAttributes(QXmlStreamWriter* xmlWriter, const QStringList &session);

    static  const QStringList helperGetHeaderLabels(const QString list);
private:
    myList m_courseList;
};

#endif // MYCOURSEXML_H
