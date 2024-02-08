#include <bits/stdc++.h>
using namespace std;

struct items{
    string name;
    int index, at, bt, ct, tat, wt;
};
void CompletionTime(vector<items> &process) {
    process[0].ct = process[0].at + process[0].bt;
    for (int i = 1; i < process.size(); i++) {
        process[i].ct = (process[i].at <= process[i - 1].ct ?
                           process[i - 1].ct + process[i].bt : process[i].bt + process[i].at);
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
void firstComeFirstServe(vector<items> &process) {
    sort(process.begin(), process.end(), [](items a, items b){
        return a.at < b.at;
    });
    CompletionTime(process);
    TurnAroundTime(process);
    WaitingTime(process);

    sort(process.begin(), process.end(), [](items a, items b){
        return a.index < b.index;
    });
}

int main() {
    int n;
    cout << "Enter the numbe of process: ";
    cin >> n;
    vector<items> process(n);
    for (int i = 0; i < n; i++) {
        process[i].index = i;
        cout << "Enter process name, arrival time and brust time: ";
        cin >> process[i].name >> process[i].at >> process[i].bt;
    }
    firstComeFirstServe(process);

    cout << "name\t at\t bt\t ct\t tat\t wt\n";
    for (auto it : process) {
        cout << it.name << '\t' << it.at << '\t' << it.bt << '\t' <<
             it.ct << '\t' << it.tat << '\t' << it.wt << '\n';
    }
}
