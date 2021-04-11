// Big O Analysis
// 2021 Christopher Digno
#include "../include/pch.h"
using namespace std;

class Timer {
private:
    chrono::time_point<chrono::high_resolution_clock> m_startTime;
    chrono::time_point<chrono::high_resolution_clock> m_endTime;
    long long ms;
    long long us;
public:
    Timer(bool immidiatelyStart) {
        ms = 0LL;
        if (immidiatelyStart == true) {
            start();
        }
    }

    void start() {
        m_startTime = chrono::high_resolution_clock::now();
    }

    void stop() {
        m_endTime = chrono::high_resolution_clock::now();

        auto alpha = chrono::time_point_cast<chrono::microseconds>(m_startTime).time_since_epoch().count();
        auto omega = chrono::time_point_cast<chrono::microseconds>(m_endTime).time_since_epoch().count();
        auto duration = omega - alpha;
        ms = duration / 1000LL;
        us = duration;
    }

    long long getms() {
        return ms;
    }

    long long getus() {
        return us;
    }

    ~Timer() {
        stop();
    }
};

void resPrintHandler(Timer &obj) {
    cout << "Time: " << obj.getms() << " ms (" << obj.getus() << " us)\n";
}

void initTimeHandler(string &name) {
    stringstream strs;
    auto now = time(0);
    tm *stm = localtime(&now);
    //testmsg_DDMMYYYY_HH:MM:SS
    strs << "res//testmsg_";
    strs << setfill('0') << setw(2) << stm->tm_mday << flush;
    strs << setfill('0') << setw(2) << 1 + stm->tm_mon << flush;
    strs << 1900 + stm->tm_year << "_";
    strs << setfill('0') << setw(2) << stm->tm_hour << flush;
    strs << setfill('0') << setw(2) << stm->tm_min << flush;
    strs << setfill('0') << setw(2) << stm->tm_sec << flush;
    name = strs.str();
}

int main() {
    string filename("");
    initTimeHandler(filename);
    ofstream file(filename);

    // >>> Testrunning 1st Algorithm <<<
    // 1. Building testcases
    {
        
    }

    file.close();
}


//Timer algo draft:
//Timer testalg(false);
//for (int i = 0; i < 5; i++) {
//    cout << "\nRun #" << i + 1 << " with iter " << iter << '\n';
//    testalg.start();
//    testingAlgo2(iter);
//    testalg.stop();
//    resPrintHandler(testalg);
//    iter *= 100;
//}