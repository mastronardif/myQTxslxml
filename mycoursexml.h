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
    static int forEachQuestion(QXmlStreamWriter* xmlWriter, const QStringList &questions, const QString m_pathImageFolder, const QString srcFileName);
    static int forEachStudent (QXmlStreamWriter* xmlWriter, const myList& ssnData, const QStringList &votes);

    static int forStudentVote(int& idxVote, const QString student, const QStringList &list, const QStringList &listPolls, QXmlStreamWriter* xmlWriter);
    static int writeStudentAttributes(QXmlStreamWriter* xmlWriter, const myList& ssnData, const QString sid);
    static int writeSessionAttributes(QXmlStreamWriter* xmlWriter, const QStringList &session);
    static int writeAggregatesForStudent(QXmlStreamWriter* xmlWriter, const QString sid, const QStringList &list);

    static QString calculateScore(const QStringList &listPolls, const QString qid, const QString ans);
    static QString calculateSessionPerformancePoints(const QStringList &listSession);
    static QString calculatePossiblePointsForQuestionN(const QStringList &listPolls, const QString idxPoll);

    // helpers
    static QString helperGetSessionDateFromFile();

private:
    myList m_courseList;

    QString srcPathFolder;
    //QString m_srcPathRemoteIds;
    QString m_pathImageFolder;
    QString srcFolderName;
    QString srcFileName;
};

#endif // MYCOURSEXML_H
