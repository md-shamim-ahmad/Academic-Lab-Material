#include <bits/stdc++.h>
using namespace std;
struct processor {
    string name; // Processor Name
    int AT; // Arrtival Time
    int BT; // Brust Time
    int CT; // Completion Time
    int TAT; // Turn Around Time
    int WT; // Waiting Time
    int priority;
};
void calculate_CompletionTime(vector<processor> &processorList) {
    processorList[0].CT = processorList[0].AT + processorList[0].BT;
    for (int i = 1; i < processorList.size(); i++) {
        processorList[i].CT = (processorList[i].AT <= processorList[i - 1].CT ?
                processorList[i].BT + processorList[i - 1].CT : processorList[i].BT +processorList[i].AT);
    }
}
void calculate_TurnAroundTime(vector<processor> &processorList) {
    for (auto & processor : processorList)
        processor.TAT = processor.CT - processor.AT;
}
void calculate_WaitingTime(vector<processor> &processorList) {
    for (auto & processor : processorList)
        processor.WT = processor.TAT - processor.BT;
}
int main() {
    int n;
    cout << "Enter the number of Processor : ";
    cin >> n;
    vector<processor> processorList(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter the Processor Name : ";
        cin >> processorList[i].name;
        cout << "Enter the Processor Arival Time : ";
        cin >> processorList[i].AT;
        cout << "Enter the Processor Brust Time : ";
        cin >> processorList[i].BT;
        cout << "Enter the Processor Priority : ";
        cin >> processorList[i].priority;
    }
    sort(processorList.begin(), processorList.end(), [](processor &a, processor &b) {
       if(a.priority == b.priority)
           return a.AT < b.AT;
        return a.priority < b.priority;
    });
    calculate_CompletionTime(processorList);
    calculate_TurnAroundTime(processorList);
    calculate_WaitingTime(processorList);
    for (auto &processor: processorList) {
        cout << processor.name << " " << processor.AT << " " << processor.BT << " "
            << processor.CT << " " << processor.TAT << " " << processor.WT << '\n';
    }
    return 0;
}
