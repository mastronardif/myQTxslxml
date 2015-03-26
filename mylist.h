#ifndef MYLIST_H
#define MYLIST_H
#include <QString>
#include <QStringList>
#include <QFile>
#include <QHash>

struct S_StudentAggregatesHeader
{
    QString sid;
    QString StudentId;
    QString RemoteId;
    QString name;
    QString StudentPointsTotalPercentage;
};

struct S_CourseEntities
{
    QString srcPathFolder;
    QString m_srcPathRemoteIds;
    QString m_srcPathStudentNames;
    QString srcPathImageFolder;
    QString srcFolderName;
    QString srcFileName;
};
//// helper

class myList
{
    enum eTerms{
        FOUND    = 1,
        NOTFOUND = 2,
    };

    static struct S_StudentAggregatesHeader StudentAggregateTableDef;
    static QString                   kStudentAggregatesHeader;

public:
    myList();

    int makeList(S_CourseEntities courseEntities, QString src);

    static int printList(QStringList list);
    static int printListToFile(QString fn, QStringList list);

    static int createAggregatedListForStudents(const QStringList& leftVotes, const QStringList& roster,  QStringList& aggregatesForStudents);
    static int createListForRemoteIds(const QString pathRemoteIds,    QStringList& destRemoteIds);
    static int createListForRemoteStudents(const QStringList& remoteIds, const QStringList& studentNames, QStringList& destRosterRemotesStudents);

    static int createListForStudentNames(const QString pathStudentNames, QStringList &destStudentNames);

    // helpers
    static eTerms helperFindAndUpdate(QStringList& destRosterRemotesStudents, const QString studentNames);

public:
    QStringList m_course;
    QStringList m_ssn;
    QStringList m_p;
    QStringList m_v;

    QStringList m_roster;   // roster contains names and clickerId's.
    QStringList m_remoteIds;   // remote ID's
    QStringList m_StudentNames;   // student names for course
    QStringList m_rosterRemotesStudents; // the outter join of __ and __.

    static  const QStringList helperGetHeaderLabels(const QString list);

    // agreagtes
    QStringList m_aggregatesForSession;
    QStringList m_aggregatesForStudents;
};

#endif // MYLIST_H
