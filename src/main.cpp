// Big O Analysis
// 2021 Christopher Digno
#include "../include/pch.h"
using namespace std;

/* Important Notes:
1. Length of arrays will be always 10
2. Testcases are hardcoded (except for random case)
*/

class Timer {
private:
    chrono::time_point<chrono::high_resolution_clock> m_startTime;
    chrono::time_point<chrono::high_resolution_clock> m_endTime;
    long long milliseconds;
public:
    Timer(bool immidiatelyStart) {
        milliseconds = 0LL;
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
        milliseconds = duration * 0.001;
    }

    void testPrint() {
        cout << milliseconds;
    }

    ~Timer() {
        stop();
    }
};

int main() {
    
}