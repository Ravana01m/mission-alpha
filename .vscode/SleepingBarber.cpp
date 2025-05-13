#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<queue>
#include<chrono>
using namespace std;
const int CHAIRS = 3; // Number of chairs in waiting room
mutex mtx;
condition_variable barberSleep;
queue<int> waitingCustomers;
bool barberSleeping = true;

void barber() {
    while (true) {
        unique_lock<mutex> lock(mtx);
        while (waitingCustomers.empty()) {
            cout << "Barber is sleeping.\n";
            barberSleep.wait(lock);
        }
        int customerID = waitingCustomers.front();
        waitingCustomers.pop();
        cout << "Barber is cutting hair of customer " << customerID << ".\n";
        lock.unlock();
        this_thread::sleep_for(chrono::seconds(2));
        cout << "Barber finished haircut of customer " << customerID << ".\n";
    }
}
void customer(int id) {
    unique_lock<mutex> lock(mtx);
    if (waitingCustomers.size() < CHAIRS) {
        waitingCustomers.push(id);
        cout << "Customer " << id << " is waiting.\n";
        barberSleep.notify_one();
    } else {
        cout << "Customer " << id << " left as no chair was available.\n";
    }
}
int main() {
    thread barberThread(barber);
    for (int i = 1; i <= 4; ++i) {
        this_thread::sleep_for(chrono::milliseconds(700));
        thread customerThread(customer, i);
        customerThread.detach();
    }
    barberThread.join();
    return 0;
}
 