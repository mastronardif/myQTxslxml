#ifndef MYLIST_H
#define MYLIST_H
#include <QString>
#include <QStringList>
#include <QFile>

class myList
{

public:
    myList();

    int makeList(QString src);

    static int printList(QStringList list);
    static int printListToFile(QString fn, QStringList list);

    static int createAggregatedListForStudents(const QStringList& leftVotes, const QStringList& roster,  QStringList& aggregatesForStudents);

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
