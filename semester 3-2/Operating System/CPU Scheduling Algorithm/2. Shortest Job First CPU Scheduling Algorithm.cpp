#include <bits/stdc++.h>
using namespace std;

struct items{
    string name;
    int index, at, bt, ct, tat, wt;
    bool complete = false;
};
void CompletionTime(vector<items> &process) {
    process[0].ct = process[0].at + process[0].bt;
    process[0].complete = true;
    for (int i = 1; i < process.size(); i++) {
        vector<items> temp;
        int ct = process[i - 1].ct;
        for (int j = 0; j < process.size(); j++) {
            if (!process[j].complete && process[j].at <= ct) {
                temp.push_back(process[j]);
            }
        }
        sort(temp.begin(), temp.end(), [](items p1, items p2){
            if (p1.bt == p2.bt)
                return p1.at < p2.at;
            return p1.bt < p2.bt;
        });
        for(int j = 0, k = i; j < temp.size(); j++) {
            process[k++] = temp[j];
        }
        process[i].complete = true;
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
void shortestJobFirst(vector<items> &process) {
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
    shortestJobFirst(process);

    cout << "name\t at\t bt\t ct\t tat\t wt\n";
    for (auto it : process) {
        cout << it.name << '\t' << it.at << '\t' << it.bt << '\t' <<
             it.ct << '\t' << it.tat << '\t' << it.wt << '\n';
    }
}
