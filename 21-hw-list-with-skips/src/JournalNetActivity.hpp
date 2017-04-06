// Артем Абрамов БПИ 151
#include "JournalNetActivity.h"

#include <fstream>

template <int numLevels>
JournalNetActivity<numLevels>::JournalNetActivity(void)
{
}

template <int numLevels>
JournalNetActivity<numLevels>::~JournalNetActivity(void)
{}

// Read the whole log from the file on fullpath
template <int numLevels>
void JournalNetActivity<numLevels>::parseLog(string fullpath)
{
    ifstream fin(fullpath); // opens the file

    TimeStamp timestamp; // dummy
    NetActivity netactivity; // dummy

    while (fin)
    {
        fin >> timestamp;
        if (!fin) break;
        fin >> netactivity.m_user;
        if (!fin) break;
        fin >> netactivity.m_host;
        if (!fin) break;

        m_Journal.insert(netactivity, timestamp);
    }
}

// Just dumps the whole journal to the out stream
template <int numLevels>
void JournalNetActivity<numLevels>::dumpJournal(ostream & out)
{
    typename TypeList::TypeNode * prehead, * run;
    prehead = m_Journal.getPreHead();
    run = prehead;

    // prehead is placed before the first and after the last element
    // So it serves two roles.
    while (run->m_next != prehead)
    {
        run = run->m_next;
        out << run->m_key;
        out << " ";
        out << run->m_value;
    }
}

// Outputs all net activity between from and to
template <int numLevels>
void JournalNetActivity<numLevels>::outputSuspiciousActivities(
    string hostSuspicious, const TimeStamp & timeFrom, const TimeStamp & timeTo) const
{
    typename TypeList::TypeNode *start, *end;
    cout << "Finding time" << endl;
    start = m_Journal.findFirst(timeFrom);
    if (start == 0)
    {
        return;
    }
    end = m_Journal.findLastLessThan(timeTo);
    if (end == 0)
    {
        return;
    }
    while (start != end)
    {
        if (start->m_value.m_host == hostSuspicious)
        {
            cout << start->m_value << endl;
        }
        start = start->m_next;
    }
}
