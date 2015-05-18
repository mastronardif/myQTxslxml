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

// as seen in the xml file.
struct S_QuestionAggregatesHeader
{
    int idx;
    int AveragePercent;
    int AveragePoints;
    QString CorrectAnswer;
    int CorrectResponses;
    int IncorrectResponses;
    int NoResponses;
    int Responses;
};

class myCourseXml
{
public:
    myCourseXml(myList &m_courseList);

    //static int printCourse(QStringList list);
    int printSession(QString outFN);

private:
    static int writeTitleElement(QXmlStreamWriter* xmlWriter, const QStringList &session);
    static int writeHdrElement(QXmlStreamWriter* xmlWriter, QStringList ColsToShow);
    static int forEachQuestion(QXmlStreamWriter* xmlWriter, const QStringList &questions, const QList<S_QuestionAggregatesHeader> &aggs, const QString m_pathImageFolder, const QString srcFileName);
    static int forEachStudent (QXmlStreamWriter* xmlWriter, const myList& ssnData, const QStringList &votes);

    static int forStudentVote(int& idxVote, const QString student, const QStringList &list, const QStringList &listPolls, QXmlStreamWriter* xmlWriter);
    static int writeStudentAttributes(QXmlStreamWriter* xmlWriter, const myList& ssnData, const QString sid);
    static int writeSessionAttributes(QXmlStreamWriter* xmlWriter, const QStringList &session, const QStringList &polls);
    static int writeAggregatesForStudent(QXmlStreamWriter* xmlWriter, const QString sid, const QStringList &list);

    static QString calculateScore(const QStringList &listPolls, const QString qid, const QString ans);
    static QString calculateSessionPerformancePoints(const QStringList &listSession, const QStringList &polls);
    //static QString calculatePossiblePointsForQuestionN(const QStringList &listPolls, const QString idxPoll);
    static double  calculatePossiblePointsForQuestion(const QStringList &listPolls, int iPollNumber);
    static double  calculateSessionPossiblePoints(const QStringList &session, int idxSession,  const QStringList &polls);

    //static QStringList aggregatesForVotes(const QStringList &listPolls, const QStringList &listVotes);
    static QList<S_QuestionAggregatesHeader> aggregatesForVotes(const QStringList &listPolls, const QStringList &listVotes);

    // helpers
    static QString helperGetSessionDateFromFile();

private:
    static QString kQuestionAggregatesHeader;
    myList m_courseList;

    QString srcPathFolder;
    //QString m_srcPathRemoteIds;
    QString m_pathImageFolder;
    QString srcFolderName;
    QString srcFileName;
};

#endif // MYCOURSEXML_H
