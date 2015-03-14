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
    int forEachStudent(QXmlStreamWriter* xmlWriter);
    static int forEachStudent00(QXmlStreamWriter* xmlWriter, const QStringList &votes);
    static int forEachStudentVote(int &idx, const QString student, const QStringList &list, QXmlStreamWriter* xmlWriter);
    static int writeStudentAttributes(QXmlStreamWriter* xmlWriter, const QString sid);

    static  const QStringList helperGetHeaderLabels(const QString list);
private:
    myList m_courseList;
};

#endif // MYCOURSEXML_H
