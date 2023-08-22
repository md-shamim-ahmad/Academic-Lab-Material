#include <bits/stdc++.h>
using namespace std;
struct processor {
    string name;
    int arrtivalTime, brustTime, brustRemainingTime, completionTime, turnAroundTime, waitingTime;
    bool isComplete, inQueue;
};

void calculateTurnAroundTime(vector<processor> &processorList) {
    for (auto &processor: processorList)
        processor.turnAroundTime = processor.completionTime - processor.arrtivalTime;
}
void calculateWaitingTime(vector<processor> &processorList) {
    for (auto &processor: processorList)
        processor.waitingTime = processor.turnAroundTime - processor.brustTime;
}
void checkNewArrivalProcess(vector<processor> &processorList, queue<int> &readyQueue, int &currentTime, int &executedPrograms) {
    for (int i = 0; i < processorList.size(); i++) {
        processor p = processorList[i];
        if (p.arrtivalTime <= currentTime && !p.isComplete && !p.inQueue) {
            processorList[i].inQueue = true;
            readyQueue.push(i);
            executedPrograms += 1;
        }
    }
}
void updateQueue(vector<processor> &processorList, queue<int> &readyQueue, int &timeQuantum, int &currentTime, int &executedPrograms) {
    int i = readyQueue.front();
    readyQueue.pop();
    if (processorList[i].brustRemainingTime <= timeQuantum) {
        processorList[i].isComplete = true;
        currentTime += processorList[i].brustRemainingTime;
        processorList[i].completionTime = currentTime;
        processorList[i].brustRemainingTime = 0;
        if (executedPrograms != processorList.size()) {
            checkNewArrivalProcess(processorList, readyQueue, currentTime, executedPrograms);
        }
    } else {
        processorList[i].brustRemainingTime -= timeQuantum;
        currentTime += timeQuantum;
        if (executedPrograms != processorList.size()) {
            checkNewArrivalProcess(processorList, readyQueue, currentTime, executedPrograms);
        }
        readyQueue.push(i);
    }
}
void roundRobin_Algorithm(vector<processor> &processorList, int &timeQuantum) {
    sort(processorList.begin(), processorList.end(), [](processor &a, processor &b) {
        return a.arrtivalTime < b.arrtivalTime;
    });
    queue<int> readyQueue;
    readyQueue.push(0);
    processorList[0].inQueue = true;
    int currentTime = 0, executedPrograms = 0;
    while (!readyQueue.empty()) {
        updateQueue(processorList, readyQueue, timeQuantum, currentTime, executedPrograms);
    }
}
int main() {
    int n, timeQuantum;
    cout << "Enter the number of Processor : ";
    cin >> n;
    vector<processor> processorList(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter the Processor Name : ";
        cin >> processorList[i].name;
        cout << "Enter the Processor Arival Time : ";
        cin >> processorList[i].arrtivalTime;
        cout << "Enter the Processor Brust Time : ";
        cin >> processorList[i].brustTime;
        processorList[i].brustRemainingTime = processorList[i].brustTime;
    }
    cout << "Enter Time Quantum : ";
    cin >> timeQuantum;

    roundRobin_Algorithm(processorList, timeQuantum);
    calculateTurnAroundTime(processorList);
    calculateWaitingTime(processorList);
    cout << "name\t at\t bt\t ct\t tat\t wt\n";
    for (auto &processor: processorList) {
        cout << processor.name << "\t" << processor.arrtivalTime << "\t" << processor.brustTime << "\t"
             << processor.completionTime << "\t" << processor.turnAroundTime << "\t" << processor.waitingTime << '\n';
    }
    return 0;
}
