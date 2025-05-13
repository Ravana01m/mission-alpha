#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::queue<int> buffer;
const unsigned int MAX_BUFFER_SIZE = 10;
const unsigned int NUM_ITEMS = 20;

std::mutex mtx;
std::condition_variable cv;
bool done = false;

void producer() {
    for (int i = 0; i < NUM_ITEMS; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return buffer.size() < MAX_BUFFER_SIZE; });

        buffer.push(i);
        std::cout << "Produced: " << i << std::endl;

        lock.unlock();
        cv.notify_all();
    }

    // Signal that production is done
    std::unique_lock<std::mutex> lock(mtx);
    done = true;
    lock.unlock();
    cv.notify_all();
}

void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !buffer.empty() || done; });

        if (!buffer.empty()) {
            int item = buffer.front();
            buffer.pop();
            std::cout << "Consumer " << id << " consumed: " << item << std::endl;
        } else if (done) {
            break;  // Exit loop if done and buffer is empty
        }

        lock.unlock();
        cv.notify_all();
    }
}

int main() {
    std::thread prod(producer);
    std::thread cons1(consumer, 1);
    std::thread cons2(consumer, 2);

    prod.join();
    cons1.join();
    cons2.join();

    return 0;
}
