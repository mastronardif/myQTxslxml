#include "mycoursexml.h"
#include <QFile>
#include <QDebug>
#include <QString>


QString myCourseXml::kQuestionAggregatesHeader = "idx,AveragePercent,AveragePoints"
        ",CorrectResponses,IncorrectResponses,NoResponses,Responses";

myCourseXml::myCourseXml(myList &courseList) : m_courseList(courseList)
{

    // TBD pass these in the constructor.
    //srcPathFolder      = "/Users/frank.mastronardi/workspace/iclicker740Sources/Debug/Classes/0Large_PHIL 102";
    srcPathFolder      = m_courseList.m_courseEntities.srcPathFolder;
    //m_srcPathRemoteIds =  srcPathFolder + "/SessionData/" + "RemoteID.csv";
    srcFolderName = "0Large_PHIL 102";

    srcFileName   = m_courseList.m_courseEntities.srcFileName; //"L1501291001.xml";

    m_pathImageFolder = QString("%1/%2/").arg(srcPathFolder, "Images");

    // Get session date from file time stamp.
}

QList<S_QuestionAggregatesHeader> myCourseXml::aggregatesForVotes(const QStringList &listPolls, const QStringList &listVotes)
{
    QStringList aggs;

    QList<S_QuestionAggregatesHeader> aggregates;

    const QStringList labelsPolls = myList::helperGetColsFromList(listPolls[0]);
    QStringList cols;
    QString  fans;
    QString line;


    S_QuestionAggregatesHeader question;
    for (int idx = 0; idx < listPolls.size(); idx++)
    {
        cols = myList::helperGetColsFromList(listPolls[idx]);
        QString qidx = cols[labelsPolls.indexOf("idx")];
        int iQidx = qidx.toInt();

        question.idx = iQidx;
        question.CorrectAnswer      = cols[labelsPolls.indexOf("cans")];
        question.AveragePoints      = 0;
        question.AveragePercent     = 0;
        question.CorrectResponses   = 0;
        question.IncorrectResponses = 0;
        question.Responses          = 0;
        question.NoResponses        = 0;

        aggregates.append(question);
    }

    if (listVotes.size() > 0)
    {
    const QStringList labelVotes = myList::helperGetColsFromList(listVotes[0]);
    for (int idx = 1; idx < listVotes.length(); idx++)
    {
        line = listVotes[idx];
        cols = myList::helperGetColsFromList(line);

        // CorrectResponses
        QString qidx = cols[labelVotes.indexOf("p_id")];
        int iQidx = qidx.toInt();
        //cols = myList::helperGetColsFromList(listPolls[qidx.toInt()]);
        fans = cols[labelVotes.indexOf("fans")];
        //cans = myList::helperGetColsFromList(listPolls[qidx.toInt()])[labelVotes.indexOf("cans")];

        if (aggregates[iQidx].CorrectAnswer.length() &&
            (0 == QString::compare(aggregates[iQidx].CorrectAnswer, fans, Qt::CaseInsensitive)) )
        {
            aggregates[iQidx].CorrectResponses += 1;
        }

        if (aggregates[iQidx].CorrectAnswer.length() &&
            (0 != QString::compare(aggregates[iQidx].CorrectAnswer, fans, Qt::CaseInsensitive)) )
        {

            aggregates[iQidx].IncorrectResponses += 1;
        }

        //
        if (fans.length())
        {
            aggregates[iQidx].Responses    += 1;
        }
        else
        {
            aggregates[iQidx].NoResponses  += 1;
        }
    }
    }
/*
    QString myCourseXml::kQuestionAggregatesHeader =
"idx,AveragePercent,AveragePoints"
            ",CorrectResponses,IncorrectResponses,NoResponses,Responses";
*/
    aggs.append(kQuestionAggregatesHeader);
    for (int idx = 1; idx < listPolls.size(); idx++)
    {
        double averagePercent =  aggregates[idx].Responses ? static_cast<double>(aggregates[idx].CorrectResponses) /  aggregates[idx].Responses : 0;
        QString row = QString("%1,%2,%3,%4,%5,%6,%7").arg(
                      QString::number(aggregates[idx].idx)
                     ,QString::number(averagePercent, 'f', 2)
                     ,QString::number(aggregates[idx].AveragePoints)
                     ,QString::number(aggregates[idx].CorrectResponses)
                     ,QString::number(aggregates[idx].IncorrectResponses)
                     ,QString::number(aggregates[idx].NoResponses)
                     ,QString::number(aggregates[idx].Responses));

        aggs.append(row);

    }
    myList::printListToFile("aggs.csv", aggs);

    return aggregates;
}

double myCourseXml::calculatePossiblePointsForQuestion(const QStringList &listPolls, int iPollNumber)
{
    const QStringList labels = myList::helperGetColsFromList(listPolls[0]);
    QStringList cols         = myList::helperGetColsFromList(listPolls[iPollNumber]);

    if (labels.length() != cols.length())
    {
        return -1;
    }

    double dAnypt = cols[labels.indexOf("anypt")].toDouble();
    double dAnspt = cols[labels.indexOf("anspt")].toDouble();
    double dPossiblePoints = dAnypt + dAnspt;

    return dPossiblePoints;
}

//QString myCourseXml::calculatePossiblePointsForQuestionN(const QStringList &listPolls, const QString idxPoll)
//{
//    // See spec for how to calculate this.
//    //"anspt";  // Correct answer points

//    QString anspt;
//    QStringList results;
//    QStringList find;
//    find << "anspt";

//    results = myList::helperFindByKeyValue(listPolls, find, "idx", idxPoll);

//    if (!results.isEmpty())
//    {
//        anspt = results[0];
//    }

//    QString pp = anspt; //"1.99"; // default

//    return pp;
//}

QString myCourseXml::calculateScore(const QStringList &listPolls, const QString qid, const QString ans)
{
    QString score = "(NR)"; // default

    const QStringList labels = myList::helperGetColsFromList(listPolls[0]);
    QStringList cols;

    for (int idx = 1; idx < listPolls.length(); idx++)
    {
        cols = myList::helperGetColsFromList(listPolls[idx]);

        QString pid = cols[labels.indexOf("idx")];
        if (pid == qid)
        {
            // Found
            break;
        }
    }

    QString cans = cols[labels.indexOf("cans")];
    if (!ans.isEmpty())
    {
         score = (cans == ans) ? "1" : "0";

    }
//    if (!ans.isEmpty() && (cans == ans) )
//    {
//        // calculate scrore
//        retval = "1";
//    }

    return score;
}

QString myCourseXml::calculateSessionPerformancePoints(const QStringList &listSession, const QStringList &polls)
{
    QString perf = "5.99";  // default;
    int iCans = 0;
    // Count cans, and not deleted from polls.
    const QStringList labels = myList::helperGetColsFromList(polls[0]);
    //const QStringList cols = myList::helperGetColsFromList(polls[1]);

    for (int idx = 1; idx < polls.length(); idx++)
    {
        const QStringList cols = myList::helperGetColsFromList(polls[idx]);

        if (cols.length() != labels.length())
        {
            //skip bad rows.
            continue;
        }
        QString isDel = cols[labels.indexOf("isDel")];
        QString cans = cols[labels.indexOf("cans")];
        if (isDel.compare("N", Qt::CaseInsensitive) == 0)
        {
            if (!cans.isEmpty())
            {
                iCans++;
            }
        }
    }

    perf = QString::number(iCans);


//    QStringList labels = myList::helperGetColsFromList(listSession[0]);
//    QStringList cols = myList::helperGetColsFromList(listSession[1]);

//    QString part = cols[labels.indexOf("part")];
    //QString perf = cols[labels.indexOf("perf")];

    //dReturnPoints = pointsPossible - participationPoints;

    return perf;

}

double myCourseXml::calculateSessionPossiblePoints(const QStringList &session, int idxSession,  const QStringList &polls)
{
    double dSessionPossiblePoints;

    const QStringList labels = myList::helperGetColsFromList(session[0]);
    const QStringList cols   = myList::helperGetColsFromList(session[idxSession]);;
    if (cols.length() != labels.length())
    {
        return -1;
    }

    double dPart      = cols[labels.indexOf("part")].toDouble();
    double dMinrep    = cols[labels.indexOf("minrep")].toDouble();
    double dMinPart_S = 1; //cols[labels.indexOf("MinPart_S")].toDouble();
    double dPossiblePoints = dPart + dMinrep + dMinPart_S;

    double dQpp = calculatePossiblePointsForQuestion(polls, 1);

    dSessionPossiblePoints = dPossiblePoints + dQpp;

    return dSessionPossiblePoints;
}

int myCourseXml::printSession(QString outFN)
{
    int iRetval = 0; // default success
    struct helperMyCourseXmlErr err;
    QFile::FileError eErr;

    QString reportxmlFN = QString("%1/Reports/%2.POC.xml").arg(srcPathFolder, srcFileName);
    QFile file(reportxmlFN);

    if (!file.open(QIODevice::WriteOnly))
    {
        //QFile::error()
        err.msg    = file.errorString();
        eErr   = file.error();
        err.msg = QString("%1, CreateXMLFile_StudentSummary() = %2, %3\n").arg(outFN, err.msg,  QString::number(eErr));
        qDebug() << err.msg ;
        //QMessageBox::warning(0, "", errMsg);
        return -1;
    }

    QXmlStreamWriter* xmlWriter = new QXmlStreamWriter();
    xmlWriter->setDevice(&file);
    xmlWriter->setAutoFormatting(true);
    xmlWriter->writeStartDocument();

//    xmlWriter->writeComment("wtf xml file outFN = " + outFN + " " +
//                            this->m_courseList.m_courseEntities.srcPathFolder);
    xmlWriter->writeStartElement("ROOT"); xmlWriter->writeAttribute("SSR",   "makeThistheRootTag");

    xmlWriter->writeStartElement("SESSION");
    writeSessionAttributes(xmlWriter, this->m_courseList.m_ssn, this->m_courseList.m_p);

    // Title

     writeTitleElement(xmlWriter, this->m_courseList.m_ssn);


    // Questions
    xmlWriter->writeStartElement("QUESTIONS");   // <QUESTIONS>

    QStringList partList = srcFileName.split(".");
    QString withoutExtension = partList[0];

    // calculate aggregates.
    QList<S_QuestionAggregatesHeader> aggsQs = aggregatesForVotes(this->m_courseList.m_p, this->m_courseList.m_v);

    //myList::printListToFile("aggs.csv", aggsQs);

    forEachQuestion(xmlWriter, this->m_courseList.m_p, aggsQs, m_pathImageFolder, withoutExtension);

    xmlWriter->writeEndElement();   // </QUESTIONS>

    xmlWriter->writeStartElement("STUDENTS");   // <STUDENTS>

    forEachStudent(xmlWriter, this->m_courseList, this->m_courseList.m_v);
    qDebug() << "report on these students:";

    xmlWriter->writeEndElement();   // </STUDENTS>

    xmlWriter->writeEndElement();   // </SESSION>

    xmlWriter->writeEndElement();   // </ROOT>

    return iRetval;
}

int myCourseXml::writeHdrElement(QXmlStreamWriter* xmlWriter, QStringList ColsToShow)
{
    //ColsToShow << "@name" << "@StudentId" << "@RemoteId";
    xmlWriter->writeStartElement("Hdr"); // <Hdr>
        if (ColsToShow.contains("@name", Qt::CaseInsensitive))
        {
            xmlWriter->writeStartElement("col"); // <col>
                xmlWriter->writeAttribute("attrib", "@name");
                xmlWriter->writeAttribute("n", "Name");
            xmlWriter->writeEndElement(); // </col>
        }
        if (ColsToShow.contains("@StudentId", Qt::CaseInsensitive))
        {
            xmlWriter->writeStartElement("col"); // <col>
                xmlWriter->writeAttribute("attrib", "@StudentId");
                xmlWriter->writeAttribute("n", "Student ID");
            xmlWriter->writeEndElement(); // </col>
        }

        if (ColsToShow.contains("@RemoteId", Qt::CaseInsensitive))
        {
            xmlWriter->writeStartElement("col"); // <col>
                xmlWriter->writeAttribute("attrib", "@RemoteId");
                xmlWriter->writeAttribute("n", "Remote or GO ID");
            xmlWriter->writeEndElement(); // </col>
        }

    xmlWriter->writeEndElement(); // </Hdr>
}

int myCourseXml::writeTitleElement(QXmlStreamWriter* xmlWriter, const QStringList &session)
{
    const QStringList labels = myList::helperGetColsFromList(session[0]);
    QStringList cols =  myList::helperGetColsFromList(session[1]); //list[1].split(rx);

    // skip 1st row aka the header
    QString name = cols[labels.indexOf("ssnn")]; //(labels.indexOf("ssnn")   != -1) ? cols[labels.indexOf("ssnn")]   : "null";

    xmlWriter->writeStartElement("TITLE");

    xmlWriter->writeAttribute("NAME", name);

    xmlWriter->writeTextElement("SESSION", "TBD");
    QString sd = "Generated: "+ QDateTime::currentDateTime().toString("MM/dd/yyyy h:m:s");

    xmlWriter->writeTextElement("sdate", sd);

    // Write HdrElement
    QStringList ColsToShow;
    ColsToShow << "@name" << "@StudentId" << "@RemoteId";
    myCourseXml::writeHdrElement(xmlWriter, ColsToShow);

    xmlWriter->writeTextElement("DATE", "4/6/15 10:01 AM  TBD from session file stamp.");
    xmlWriter->writeTextElement("SESSIONID", "sessionIndex-0");
//    <TITLE NAME="Q2 1/29 and 2/3">
//        <SESSION>0Large_PHIL 102</SESSION>
//        <sdate>Generated: 03/11/2015 16:55:25</sdate>
//        <Hdr>
//            <col attrib="@name" n="Name"/>
//            <col attrib="@StudentId" n="Student ID"/>
//            <col attrib="@RemoteId" n="Remote or GO ID"/>
//        </Hdr>
//        <DATE>1/29/15 10:01 AM</DATE>
//        <SESSIONID>sessionIndex-0</SESSIONID>
//    </TITLE>

    xmlWriter->writeEndElement(); // </TITLE>
}

int myCourseXml::writeSessionAttributes(QXmlStreamWriter* xmlWriter, const QStringList &session,  const QStringList &polls)
{
    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QStringList list  = session;

    const QStringList labels = myList::helperGetColsFromList(session[0]);
    QStringList cols; // = list[1].split(rx);

    // skip 1st row aka the header
    for(int idx = 1; idx < list.length(); idx++)
    {
        cols = myList::helperGetColsFromList(session[idx]); //line.split(rx);
        if (cols.length() != labels.length())
        {
            //skip bad rows.
            continue;
        }

        QString name = cols[labels.indexOf("ssnn")];
        QString part = cols[labels.indexOf("part")];

        xmlWriter->writeAttribute("part", part);
        //Partic="0.00" ap="0.71" avg="2.85" part="0.00" perf="4.00" pp="4.00" sppp="4.00"
        xmlWriter->writeAttribute("Partic", "0.00");
        xmlWriter->writeAttribute("ap", "0.71");
        xmlWriter->writeAttribute("avg", "2.85");
        //xmlWriter->writeAttribute("part", "0.00");

        // QString::number(Session->getPerformancePoints(), 'f',2));
        QString perf = calculateSessionPerformancePoints(session, polls);
        xmlWriter->writeAttribute("perf", perf); // "4.99");

        double dSessionPossiblePoints = calculateSessionPossiblePoints(session, idx, polls);
        QString sessionPossiblePoints = QString::number(dSessionPossiblePoints, 'f', 2);

        xmlWriter->writeAttribute("pp",   sessionPossiblePoints);
        xmlWriter->writeAttribute("sppp", sessionPossiblePoints);
    }
}

int myCourseXml::writeAggregatesForStudent(QXmlStreamWriter* xmlWriter, const QString sid, const QStringList &list)
{    
    xmlWriter->writeAttribute("ClassAveragePerformancePercentage", "0,00");
    xmlWriter->writeAttribute("ClassAveragePointsPerformance",       "15.64");
    xmlWriter->writeAttribute("ClassAveragePointsTotal",       "45.99");
    xmlWriter->writeAttribute("ClassAveragePointsTotalPercentage",       "15.64");
    xmlWriter->writeAttribute("Partic",       "0.00");
    xmlWriter->writeAttribute("Perform",       "4,707.00");
    xmlWriter->writeAttribute("PossiblePointsParticipation",       "0.00");
    xmlWriter->writeAttribute("PossiblePointsPerformance",       "9.00");
    xmlWriter->writeAttribute("PossiblePointsTotal",       "34.00");
    xmlWriter->writeAttribute("StudentPointsParticipation",       "0.00");
    xmlWriter->writeAttribute("StudentPointsPerformance",       "34.00");
    xmlWriter->writeAttribute("StudentPointsPerformancePercentage",       "45.99");
    xmlWriter->writeAttribute("StudentPointsTotalPercentage",       "9.00");
    xmlWriter->writeAttribute("Total",       "4,707.00");

    xmlWriter->writeAttribute("n",       "look up name");
    //xmlWriter->writeAttribute("name",       "tbd");

    xmlWriter->writeAttribute("partipationtotal",       "0.00");
    xmlWriter->writeAttribute("rid",       "");
    xmlWriter->writeAttribute("scorepercent",       "999.99");
    xmlWriter->writeAttribute("studentperf",                         "16.00");
    xmlWriter->writeAttribute("studentperfpercent",                  "47.06");
}

int myCourseXml::writeStudentAttributes(QXmlStreamWriter* xmlWriter, const myList& ssnData, const QString rId)
{
    xmlWriter->writeAttribute("sid",  rId);

    xmlWriter->writeAttribute("RemoteId",  rId);

    // lookup name by studentId.
    QStringList find;
    find << "StudentId" << "Last Name" << "First Name";
    QStringList results = myList::helperFindByKeyValue(ssnData.m_rosterRemotesStudents, find, "RemoteId", rId);
    QString name;
    QString studentId;
    if (results.length() == 3)
    {
        studentId = results[0];
        name = results[1] + ' ' + results[2];
    }

    xmlWriter->writeAttribute("StudentId",  studentId);
    xmlWriter->writeAttribute("name", name);
}

int myCourseXml::forEachQuestion(QXmlStreamWriter* xmlWriter, const QStringList &questions, const QList<S_QuestionAggregatesHeader> &aggs, const QString srcPathImageFolder, const QString srcFileName)
{
    QStringList list  = questions; //this->m_courseList.m_p;

    const QStringList labels = myList::helperGetColsFromList(questions[0]);
    QStringList cols; // = list[1].split(rx);

    for(int idx = 1; idx < list.length(); idx++)
    {
        QString line = list[idx];
        cols = myList::helperGetColsFromList(questions[idx]);

        //cols = line.split(rx);
        if (cols.length() != labels.length())
        {
            //skip bad rows.
            continue;
        }

        QString pollIdx = cols[labels.indexOf("idx")];

        QString qn   = cols[labels.indexOf("qn")];
        QString cans = cols[labels.indexOf("cans")];

        xmlWriter->writeStartElement("question");
        xmlWriter->writeAttribute("name", qn);
        xmlWriter->writeAttribute("CorrectAnswer",   cans);

        QString id = QString("q%1").arg(QString::number(idx));
        xmlWriter->writeAttribute("id", id);

        QString questionFileName = QString("%1_Q%2.jpg").arg(srcFileName, QString::number(idx));
        QString path = QString("%1%2").arg(srcPathImageFolder, questionFileName);
        xmlWriter->writeAttribute("desktopImage",  path);
        xmlWriter->writeAttribute("file",          questionFileName);

        // TBD write question attributes
        //<question AveragePercent="0.00" AveragePoints="0.00" CorrectAnswer="" CorrectResponses="0"
        //IncorrectResponses="0" NoResponses="0" Responses="262" desktopImage="/Users/frank.mastronardi/workspace/iclicker740Sources/Debug/Classes/0Large_PHIL 102/Images/L1501291001_Q1.jpg" file="L1501291001_Q1.jpg"
        //id="q1" name="Question 1" possiblePoints="1.00" pp="1.00"/>
        double averagePoints =  aggs[idx].Responses ? (static_cast<double>(aggs[idx].CorrectResponses) /  aggs[idx].Responses) : 0;

        xmlWriter->writeAttribute("AveragePercent",     QString::number(aggs[idx].AveragePercent));
        xmlWriter->writeAttribute("AveragePoints",      QString::number(averagePoints, 'f', 2));
        xmlWriter->writeAttribute("CorrectResponses",   QString::number(aggs[idx].CorrectResponses));
        xmlWriter->writeAttribute("IncorrectResponses", QString::number(aggs[idx].IncorrectResponses));
        xmlWriter->writeAttribute("NoResponses",        QString::number(aggs[idx].NoResponses));
        xmlWriter->writeAttribute("Responses",          QString::number(aggs[idx].Responses));

        //mlWriter->writeAttribute("possiblePoints", ql.toString(Session->getCorrectAnswerPoints() +  Session->getResponseAnyChoicePoints(),'f',2));

        //QString possiblePoints = calculatePossiblePointsForQuestionN(questions, pollIdx);
        //QString possiblePoints = calculatePossiblePointsForQuestionN(questions, pollIdx);
        double  dPossiblePoints = calculatePossiblePointsForQuestion(questions, idx);

        QString possiblePoints = QString::number(dPossiblePoints, 'f', 2);

        xmlWriter->writeAttribute("possiblePoints",  possiblePoints);
        xmlWriter->writeAttribute("pp",  possiblePoints);


        xmlWriter->writeEndElement(); // </question>
    }
}

int myCourseXml::forEachStudent(QXmlStreamWriter* xmlWriter,  const myList& ssnData, const QStringList &votes)
{
    //** Note both students and votes are sorted by remoteId
    //** so you do NOT have to search all the votes every time.
    //** this makes it faster, But relies on it beeing sorted and in sync.
    //** If this becomes a problem go back to the linear search.

    QStringList listVotes  = votes; //this->m_courseList.m_v;
    QStringList listStudents = ssnData.m_StudentVotes;

    const QStringList labels = myList::helperGetColsFromList(listStudents[0]); //votes[0]);
    QStringList cols; // = myList::helperGetHeaderLabels(); //list[1].split(rx);

    int studentCount=1;
    int idxVote = 1;
    for(int idx = 1; idx < listStudents.length(); idx++)
    {
        QString line = listStudents[idx];

        cols = myList::helperGetColsFromList(line); //line.split(rx);

        if (cols.length() < labels.length())  // be safe
        {
            // skip ignorable rows
            continue;
        }

        QString rId = cols[labels.indexOf("RemoteId")];

        xmlWriter->writeStartElement("student");   //<student>
        writeStudentAttributes(xmlWriter, ssnData, rId);

        xmlWriter->writeAttribute("idx",  QString::number(studentCount++));
        {
            QStringList studentAgregates;  // calc agregates
            writeAggregatesForStudent(xmlWriter, rId, studentAgregates);
            //writeStudentAggregatesForStudent(sid); // BySession
            //writeSessionAggregatesForSession(thisSession);
        }

        xmlWriter->writeStartElement("qr");   //<qr>

        //forStudentVote(idxVote, rId, listVotes, xmlWriter);
        forStudentVote(idxVote, rId, listVotes, ssnData.m_p, xmlWriter);

        xmlWriter->writeEndElement();        // </qr>

        xmlWriter->writeEndElement();  // </student>
    }
}

int myCourseXml::forStudentVote(int& idxVote, const QString argRid, const QStringList &votes, const QStringList &listPolls, QXmlStreamWriter* xmlWriter)
{
    const QStringList labels = myList::helperGetColsFromList(votes[0]);

    //QString clean;
    QString rId = argRid;

    // find by RemoteId
    for(; idxVote < votes.length(); idxVote++)
    {
        QStringList cols = myList::helperGetColsFromList(votes[idxVote]);
        if (cols.length() < labels.length())  // be safe
        {
            // skip ignorable rows
            continue;
        }

        QString ss1 = cols[labels.indexOf("id")];

        // break on match.
        if (QString::compare(ss1, rId, Qt::CaseInsensitive) == 0) { break; }
    }

    for(; idxVote < votes.length(); idxVote++)
    {
        //const QString line = votes[idxVote];

        QStringList cols = myList::helperGetColsFromList(votes[idxVote]);
        if (cols.length() < labels.length())  // be safe
        {
            // skip ignorable rows
            continue;
        }

        QString pid = cols[labels.indexOf("p_id")];
        QString ss1 = cols[labels.indexOf("id")];
        QString qid = cols[labels.indexOf("p_id")];
        QString ans = cols[labels.indexOf("ans")];

        QString score = calculateScore(listPolls, qid, ans);

        qid = QString("q%1").arg(qid);

        if (QString::compare(ss1, rId, Qt::CaseInsensitive) != 0) { break; }

        xmlWriter->writeStartElement("q");   // <q>

        xmlWriter->writeAttribute("id",  qid);

        xmlWriter->writeAttribute("score",  score); //"0");

        QStringList find;
        find << "cans";
        QStringList cans = myList::helperFindByKeyValue(listPolls, find, "idx", pid);
        QString strCans = cans.isEmpty() ? "" : cans[0];
        // yes, no, indetermined.
        QString icr = strCans.isEmpty() ? "-1" :
                     (strCans.compare(ans, Qt::CaseInsensitive) == 0) ? "1" : "0";

        xmlWriter->writeAttribute("icr", icr);

        xmlWriter->writeAttribute("vote", ans);
        xmlWriter->writeAttribute("Response", ans);

        xmlWriter->writeEndElement(); // </q>
    }
}

QString myCourseXml::helperGetSessionDateFromFile()
{
    return "4/5/15 10:01 AM";
}
//QString clsSession::getSessionDateFromFile(){
//    readXmlFile();
//    xEle = xDoc->documentElement();
//    QString retValue = xEle.attribute(ClsXml::qRoot_CreatedDateAndTimeSignature_TG, "");
//    if (retValue.trimmed() == "") {
//        QFileInfo info(sessionFileName);
//        QString fDate = "";

//        fDate = info.fileName();
//        fDate = fDate.mid(1,fDate.indexOf(QString(".")) - 1);
//        fDate = fDate.left(6);
//        retValue = fDate;

//    } else {
//        retValue = retValue.left(6);
//    }
//    return retValue;
//}
