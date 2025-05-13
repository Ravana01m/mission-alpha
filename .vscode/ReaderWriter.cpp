#include <iostream>
#include <thread>
#include <mutex> 
#include <condition_variable>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

mutex resource_mutex;
mutex reader_count_mutex;
condition_variable reader_cv, writer_cv;
int reader_count = 0, writer_count = 0;
bool writer_waiting = false;

random_device rd;
mt19937 gen(rd()); 
uniform_int_distribution<> dis(100, 500);

void read(int reader_id) {
    {
        unique_lock<mutex> lock(reader_count_mutex);
        reader_cv.wait(lock, [] { return !writer_waiting; });

        reader_count++;
        if (reader_count == 1) {
            resource_mutex.lock();
        }

        cout << "Reader " << reader_id << " is reading." << endl;
    }

    this_thread::sleep_for(chrono::milliseconds(dis(gen)));

    {
        unique_lock<mutex> lock(reader_count_mutex);
        cout << "Reader " << reader_id << " has finished reading." << endl; 
        reader_count--;
        if (reader_count == 0) {
            resource_mutex.unlock();
            writer_cv.notify_one();
        }
    }
}

void write(int writer_id) { 
    {
        unique_lock<mutex> lock(reader_count_mutex);
        writer_count++;
        writer_waiting = true; 

        writer_cv.wait(lock, [] { return reader_count == 0; });
        resource_mutex.lock();

        cout << "Writer " << writer_id << " is writing." << endl;
    }

    this_thread::sleep_for(chrono::milliseconds(dis(gen)));

    {
        unique_lock<mutex> lock(reader_count_mutex);
        cout << "Writer " << writer_id << " has finished writing." << endl;
        writer_count--;
        writer_waiting = writer_count > 0;
        resource_mutex.unlock();
        if (writer_waiting) {
            writer_cv.notify_one();
        } else {
            reader_cv.notify_all();
        }
    }
}

int main() { // Main function
    vector<thread> readers; 
    vector<thread> writers;

    for (int i = 1; i <= 5; ++i) { 
        readers.push_back(thread(read, i));
        writers.push_back(thread(write, i));
    }

    for (auto& t : readers) t.join();
    for (auto& t : writers) t.join();

    return 0;
}