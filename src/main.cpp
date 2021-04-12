// Big O Analysis
// 2021 Christopher Digno
#include "../include/pch.h"
using namespace std;

#define INITRD(low, high) random_device randev;                                 \
                          mt19937 gen(randev());                                \
                          uniform_int_distribution<int> dist((low), (high))     

class Timer {
private:
    chrono::time_point<chrono::high_resolution_clock> m_startTime;
    chrono::time_point<chrono::high_resolution_clock> m_endTime;
    long long ms;
    long long us;
public:
    Timer(bool immidiatelyStart) {
        us = 0LL;
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

void _debugTestPrint(Timer &obj) {
    cout << "Time: " << obj.getms() << " ms (" << obj.getus() << " us)\n";
}

void initTimeHandler(string &name) {
    stringstream strs;
    auto now = time(0);
    tm *stm = localtime(&now);
    //testmsg_DDMMYYYY_HH:MM:SS.csv
    strs << "res//testmsg_";
    strs << setfill('0') << setw(2) << stm->tm_mday << flush;
    strs << setfill('0') << setw(2) << 1 + stm->tm_mon << flush;
    strs << 1900 + stm->tm_year << "_";
    strs << setfill('0') << setw(2) << stm->tm_hour << flush;
    strs << setfill('0') << setw(2) << stm->tm_min << flush;
    strs << setfill('0') << setw(2) << stm->tm_sec << flush;
    strs << ".csv";
    name = strs.str();
}

template <typename Ft>
void testWithFunctor(Ft func, string case_name, ofstream &file, vector<vector<int>> thiscase, 
                     int num_case = 20, int multiplier = 500) {
    int *arr = nullptr;
    Timer test(false);
    for (int i = 1; i <= num_case; i++) {
        test.start();
        arr = thiscase[i - 1].data();
        func(arr, (i * multiplier));
        test.stop();
        cout << "Length: " << i * multiplier << ": ";
        file << case_name << ',' << i * multiplier << "," << test.getus() << '\n';
        _debugTestPrint(test);
    }
}

void testingAlgo3(string *teststr, string case_name, ofstream &file) {
    Timer test(true);
    for (int i = 0; i < 20; i++) {
        test.start();
        eraseAT(teststr[i]);
        test.stop();
        cout << "Length: " << (i + 1) * 500 << ": ";
        file << case_name << ',' << (i + 1) * 500 << "," << test.getus() << '\n';
        _debugTestPrint(test);
    }
}

int main() {
    string filename("");
    initTimeHandler(filename);
    ofstream file(filename);
    file << "alg#,n,time(us)" << '\n';

    // Generating 2 arrays for 1st and 2nd Algorithm's random case
    // -> Ever since those 2 algorithms basically will be fed
    //    with the same data, we can also find out which is more effective
    cout << "Generating testcases...\n";
    vector<vector <int>> rdcase1, rdcase2;
    vector<int> vecbuf1;
    INITRD(0, 9999);
    for (int i = 500; i < 10001; i += 500) {
        for (int j = 0; j < i; j++) {
            vecbuf1.push_back(dist(gen));
        }
        rdcase1.push_back(vecbuf1);
        vecbuf1.clear();
    }
    rdcase2 = rdcase1;

    // Generating 2 arrays for 1st and 2nd Algorithm's best and worst
    // case, which is just a sorted and a reverse-sorted number sequence
    vector<vector<int>> btcase;
    vector<int> vecbuf;
    for (int i = 500; i < 10001; i += 500) {
        for (int j = 0; j < i; j++) {
            vecbuf.push_back(j);
        }
        btcase.push_back(vecbuf);
        vecbuf.clear();
    }
    vector<vector<int>> wscase = btcase;
    for (int i = 0; i < wscase.size(); i++) {
        reverse(wscase[i].begin(), wscase[i].end());
    }
    cout << "Generating done.\n";

    {   // >>> Testrunning 1st Algorithm <<<
        // 1. Testing to the algorithm, noting the time spent. Steps -> convert vector data to int*, and then
        //    pass it to the algorithm.
        cout << "=== 1st Algorithm ===\n  = Random Case =\n";
        testWithFunctor(STAY, "1", file, rdcase1);
        cout << "Algorithm 1's test done, result's exported.\n";

        // 2. Testing for best and worst case
        cout << "  = Best Case =\n";
        testWithFunctor(STAY, "1best", file, btcase);
        cout << "Best case test done\n  = Worst Case =\n";
        testWithFunctor(STAY, "1worst", file, wscase);
        cout << "Worst case done. 1st Algorithm testing done.\n";
    }

    {   // >>> Testrunning 2nd Algorithm <<<
        // 1. Testing for random case
        cout << "=== 2nd Algorithm ===\n  = Random Case =\n";
        testWithFunctor(HOME, "2random", file, rdcase2);

        // 2. Testing for best and worst case
        cout << "  = Best Case =\n";
        testWithFunctor(HOME, "2best", file, btcase);
        cout << "Best case test done\n  = Worst Case =\n";
        testWithFunctor(HOME, "2worst", file, wscase);
        cout << "Worst case done. 2nd Algorithm testing done.\n";
    }

    {   // >>> Testrunning 3rd Algorithm <<<
        // 1. Generate random string using ascii table, 20 random strings from 500 - 10000 string length,
        //    will use ASCII 32 - 126
        cout << "=== 3rd Algorithm ===\nGenerating Testcases...\n";
        string strmain[20];
        int inbuf = 0;
        INITRD(32, 126);
        for (int i = 500; i < 10001; i += 500) {
            for (int j = 0; j < i; j++) {
                strmain[inbuf].push_back((char)dist(gen));
            }
            inbuf++;
        }
        cout << "Testcases generated. Testing for random case...\n";


        // 2. Generate best and worst case string.
        //    Worst case string will be filled with char '[', '|', ':', ']' (eg. {[, |, :, ], [, ...})
        //    Best case string will be filled with one, uniform char filling the entire string (eg. {a, a, a, a, ...})
        string strbc[20], strwc[20];
        char wcchars[4] = { '[', '|', ':', ']' };
        inbuf = 0;
        for (int i = 500; i < 10001; i += 500) {
            for (int j = 0; j < i; j++) {
                strbc[inbuf].push_back('a');
                strwc[inbuf].push_back(wcchars[j % 4]);
            }
            inbuf++;
        }

        // 3. Test the algorithm
        cout << "=== Algorithm 3 ===\n   = Random Case =\n";
        testingAlgo3(strmain, "3random", file);
        cout << "Random Case done.\n   = Best Case =\n";
        testingAlgo3(strbc, "3best", file);
        cout << "Best Case done.\n   = Worst Case =\n";
        testingAlgo3(strwc, "3worst", file);
        cout << "Test done. Program closing...\n";
    }

    file.close();
}