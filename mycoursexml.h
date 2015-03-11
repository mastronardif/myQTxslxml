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

private:
    myList m_courseList;
};

#endif // MYCOURSEXML_H
