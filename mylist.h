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
    QString partic;

    static int appendOrUpdate(const QString StudentId, const S_StudentAggregatesHeader &source, QStringList &dest);
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
        eFOUND    = 1,
        eNOTFOUND = 2,
    };

    static struct S_StudentAggregatesHeader StudentAggregateTableDef;
    static QString                   kStudentAggregatesHeader;
public:
    static const QRegExp kRx;

public:
    myList();

    int makeList(S_CourseEntities courseEntities, QString src);

    static int printList(QStringList list);
    static int printListToFile(QString fn, QStringList list);

    static int createAggregatedListForStudents(const QStringList& leftVotes, const QStringList& roster,  QStringList& aggregatesForStudents);
    static int createListForRemoteIds(const QString pathRemoteIds,    QStringList& destRemoteIds);
    static int createListForRemoteStudents(const QStringList& remoteIds, const QStringList& studentNames, QStringList& destRosterRemotesStudents);

    static int createListForStudentNames(const QString pathStudentNames, QStringList &destStudentNames);
    static int createListForStudentVotes(const QStringList& students, const QStringList& rosterRemotesStudents, const QStringList& votes,  QStringList& StudentVotes);
    static int createListOfStudentsAbscent(const QStringList& students, const QStringList& rosterRemotesStudents, const QMap<QString, int> uniqueClickerIds, QStringList& studentsAbscent);

    // helpers
        //static  const QStringList helperGetHeaderLabels(const QString comaList);
    static const QStringList helperGetColsFromList(const QString comaList);
    static eTerms      helperFindAndUpdate(QStringList& destRosterRemotesStudents, const QString studentNames);
    static QStringList helperFindByKeyValue(const QStringList list, const QStringList whatToFind, const QString keyName, const QString keyValue);
    static void        helperTrimmed(QStringList& list);
public:
    S_CourseEntities m_courseEntities;
    QStringList m_course;
    QStringList m_ssn;
    QStringList m_p;
    QStringList m_v;

    QStringList m_roster;   // roster contains names and clickerId's.
    QStringList m_remoteIds;   // remote ID's
    QStringList m_StudentNames;   // student names for course
    QStringList m_rosterRemotesStudents; // the outter join of __ and __.
    QStringList m_StudentVotes;   // student names and votes includes abscenses.

    // agreagtes
    QStringList m_aggregatesForSession;
    QStringList m_aggregatesForStudents;
};

#endif // MYLIST_H
