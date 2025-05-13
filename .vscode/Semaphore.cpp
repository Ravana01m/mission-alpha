#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
class Semaphore {
    int count;
    mutex mtx;
    condition_variable cv;
public:
    Semaphore(int val = 1) : count(val) {}
    void wait() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]() { return count > 0; });
        count--;
    }
    void signal() {
        unique_lock<mutex> lock(mtx);
        count++;
        cv.notify_one();
    }
};
Semaphore sem(1);
void criticalSection(int id) {
    sem.wait();
    cout << "Thread " << id << " entering critical section.\n";
    this_thread::sleep_for(chrono::seconds(1)); // simulate work
    cout << "Thread " << id << " leaving critical section.\n";
    sem.signal();
}
int main() {
    thread t1(criticalSection, 1);
    thread t2(criticalSection, 2);
    thread t3(criticalSection, 3);
    t1.join();
    t2.join();
    t3.join();
}
