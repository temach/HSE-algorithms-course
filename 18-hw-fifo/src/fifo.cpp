#include <queue>
#include <fstream>
#include <stdexcept>

#include "fifo.h"

string choose_tense(int number_of_pages)
{
    return number_of_pages > 1 ? " pages " : " page ";
}

string get_basename(string file)
{
    // returns base name of file, without the extension
    if (file.size() < 5)
        throw invalid_argument("Invalid file name");
    // because size of ".run" string == 4
    return file.substr(0, file.size() - 4);
}

fifo::fifo(int seconds_per_page)
    : simulator(seconds_per_page)
{
}

void fifo::simulate(string file)
{
    // load data
    loadworkload(file);

    // set up simulation variables
    queue<event> waiting{};

    // so in the beginning time = 0
    int time = -1;
    int total_jobs = 0;
    int busy_time = 0;
    int total_latency = 0;

    // open file
    ofstream outfile{get_basename(file) + ".out"};
    if (! outfile.is_open())
        throw runtime_error("Could not open file");

    // write header
    outfile << "FIFO Simulation" << endl;
    outfile << endl;

    // while work is still arriving or is being served
    while (workload.size() > 0 || waiting.size() > 0)
    {
        time++;
        // there may be multiple items arriving at the same time
        while (time == workload.front().arrival_time())
        {
            const event& ev = workload.front();
            // add to waiting queue
            waiting.push(ev);
            total_jobs++;
            // print info
            outfile << "Arriving: "
                << ev.getjob().getnumpages() << choose_tense(ev.getjob().getnumpages()) + "from "
                << ev.getjob().getuser() << " at "
                << ev.arrival_time() << " seconds"
                << endl;
            // remove from workload queue
            workload.pop();
        }
        // if printer is idle and we have a job to do
        if (waiting.size() > 0 && busy_time == 0)
        {
            const event& ev = waiting.front();
            // print info
            outfile << "Servicing: "
                << ev.getjob().getnumpages() << choose_tense(ev.getjob().getnumpages()) + "from "
                << ev.getjob().getuser() << " at "
                << time << " seconds"
                << endl;
            // reset busy time
            busy_time = ev.getjob().getnumpages() * seconds_per_page;
            // calculate how much the job had to wait
            total_latency += time - ev.arrival_time();
            waiting.pop();
        }
        // simulate processing
        if (busy_time > 0)
            busy_time--;
    }

    // print footer
    outfile << endl;
    outfile << "Total jobs: " << total_jobs << " seconds" << endl;
    outfile << "Aggregate latency: " << total_latency << " seconds" << endl;
    outfile << "Mean latency: " << total_latency / (double)total_jobs << " seconds" << endl;

    // close output file
    outfile.close();

    return;
}
