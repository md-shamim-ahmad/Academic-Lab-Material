#include <bits/stdc++.h>
using namespace std;

class CountSemaphore {
public:
    explicit CountSemaphore(int count) : count_(count) {}

    void wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (count_ == 0) {
            condition_.wait(lock);
        }
        count_--;
    }

    void signal() {
        std::unique_lock<std::mutex> lock(mutex_);
        count_++;
        condition_.notify_one();
    }

private:
    int count_;
    std::mutex mutex_;
    std::condition_variable condition_;
};

int main() {
    CountSemaphore semaphore(5); // Initialize counting semaphore with count 5

    // Example usage
    for (int i = 0; i < 10; ++i) {
        std::thread([&semaphore, i]() {
            semaphore.wait();
            std::cout << "Thread " << i << " enters the critical section." << std::endl;
            // Simulate some work in the critical section
            std::this_thread::sleep_for(std::chrono::seconds(1));
            semaphore.signal();
            std::cout << "Thread " << i << " exits the critical section." << std::endl;
        }).detach();
    }

    // Sleep to allow threads to complete their work
    std::this_thread::sleep_for(std::chrono::seconds(10));

    return 0;
}
