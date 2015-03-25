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
    QString srcPathImageFolder;
    QString srcFolderName;
    QString srcFileName;
};
//// helper

class myList
{
    static struct S_StudentAggregatesHeader StudentAggregateTableDef;
    static QString                   kStudentAggregatesHeader;

public:
    myList();

    int makeList(S_CourseEntities courseEntities, QString src);

    static int printList(QStringList list);
    static int printListToFile(QString fn, QStringList list);

    static int createAggregatedListForStudents(const QStringList& leftVotes, const QStringList& roster,  QStringList& aggregatesForStudents);
    static int createListForRoster(const QString pathRemoteIds, QStringList m_roster);
public:
    QStringList m_course;
    QStringList m_ssn;
    QStringList m_p;
    QStringList m_v;

    QStringList m_roster;   // roster for course

    static  const QStringList helperGetHeaderLabels(const QString list);

    // agreagtes
    QStringList m_aggregatesForSession;
    QStringList m_aggregatesForStudents;
};

#endif // MYLIST_H
