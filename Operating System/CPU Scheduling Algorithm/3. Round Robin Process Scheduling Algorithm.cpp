#include <bits/stdc++.h>
using namespace std;

struct items{
    string name;
    int index, at, bt, ct, tat, wt, rt;
    bool complete, enQueue;
};
void newArrivalProcess(vector<items> &process, queue<int> &readyQueue, int &currentTime) {
    for (int i = 0; i < process.size(); i++) {
        if (!process[i].complete && process[i].at <= currentTime && !process[i].enQueue) {
            readyQueue.push(i);
            process[i].enQueue = true;
        }
    }
}

void updateProcess(vector<items> &process, queue<int> &readyQueue, int tQ, int &currentTime) {
    int i = readyQueue.front();
    readyQueue.pop();
    if (process[i].rt <= tQ) {
        process[i].complete = true;
        currentTime += min(process[i].rt, tQ);
        process[i].rt = 0;
        process[i].ct = currentTime;
        newArrivalProcess(process, readyQueue, currentTime);
    }
    else {
        process[i].rt -= tQ;
        currentTime += tQ;
        newArrivalProcess(process, readyQueue, currentTime);
        readyQueue.push(i);
    }
}
void CompletionTime(vector<items> &process, int tQ) {
    queue<int> readyQueue;
    readyQueue.push(0);
    process[0].enQueue = true;
    int currentTime = 0;
    while (!readyQueue.empty()) {
        updateProcess(process, readyQueue, tQ, currentTime);
    }
}
void TurnAroundTime(vector<items> &process) {
    for (int i = 0; i < process.size(); i++) {
        process[i].tat = process[i].ct - process[i].at;
    }
}
void WaitingTime(vector<items> &process) {
    for (int i = 0; i < process.size(); i++) {
        process[i].wt = process[i].tat - process[i].bt;
    }
}
void roundRobin(vector<items> &process, int tQ) {
    sort(process.begin(), process.end(), [](items a, items b){
        return a.at < b.at;
    });

    CompletionTime(process, tQ);
    TurnAroundTime(process);
    WaitingTime(process);

    sort(process.begin(), process.end(), [](items a, items b){
        return a.index < b.index;
    });
}

int main() {
    int n, tQ;
    cout << "Enter the numbe of process: ";
    cin >> n;
    vector<items> process(n);
    for (int i = 0; i < n; i++) {
        process[i].index = i;
        cout << "Enter process name, arrival time and brust time: ";
        cin >> process[i].name >> process[i].at >> process[i].bt;
        process[i].rt = process[i].bt;
    }
    cout << "Enter Time Quantum : ";
    cin >> tQ;

    roundRobin(process, tQ);

    cout << "name\t at\t bt\t ct\t tat\t wt\n";
    for (auto it : process) {
        cout << it.name << '\t' << it.at << '\t' << it.bt << '\t' <<
             it.ct << '\t' << it.tat << '\t' << it.wt << '\n';
    }
}
