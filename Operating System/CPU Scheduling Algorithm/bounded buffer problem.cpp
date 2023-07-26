#include <bits/stdc++.h>

using namespace std;

const int BUFFER_SIZE = 5;
const int NUM_PRODUCE = 20;

queue<int> buffer;
mutex mtx;
condition_variable bufferNotFull, bufferNotEmpty;

void producer() {
    for (int i = 0; i < NUM_PRODUCE; ++i) {
        unique_lock<mutex> lock(mtx);

        // Wait until the buffer is not full
        bufferNotFull.wait(lock, [] { return buffer.size() < BUFFER_SIZE; });

        buffer.push(i);
        cout << "Producing: " << i << " (Buffer size: " << buffer.size() << ")" << endl;

        lock.unlock();
        bufferNotEmpty.notify_one();
    }
}

void consumer() {
    for (int i = 0; i < NUM_PRODUCE; ++i) {
        unique_lock<mutex> lock(mtx);

        // Wait until the buffer is not empty
        bufferNotEmpty.wait(lock, [] { return !buffer.empty(); });

        int item = buffer.front();
        buffer.pop();
        cout << "Consuming: " << item << " (Buffer size: " << buffer.size() << ")" << endl;

        lock.unlock();
        bufferNotFull.notify_one();
    }
}

int main() {
    thread producerThread(producer);
    thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}
