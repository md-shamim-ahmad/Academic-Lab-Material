#include <bits/stdc++.h>
using namespace std;

struct items{
    string name;
    int index, at, bt, ct, tat, wt;
};
void CompletionTime(vector<items> &processor) {
    processor[0].ct = processor[0].at + processor[0].bt;
    for (int i = 1; i < processor.size(); i++) {
        processor[i].ct = (processor[i].at <= processor[i - 1].ct ?
                processor[i - 1].ct + processor[i].bt : processor[i].bt + processor[i].at);
    }
}
void TurnAroundTime(vector<items> &processor) {
    for (int i = 0; i < processor.size(); i++) {
        processor[i].tat = processor[i].ct - processor[i].at;
    }
}
void WaitingTime(vector<items> &processor) {
    for (int i = 0; i < processor.size(); i++) {
        processor[i].wt = processor[i].tat - processor[i].bt;
    }
}
void firstComeFirstServe(vector<items> &processor) {
    sort(processor.begin(), processor.end(), [](items a, items b){
        return a.at < b.at;
    });
    CompletionTime(processor);
    TurnAroundTime(processor);
    WaitingTime(processor);

    sort(processor.begin(), processor.end(), [](items a, items b){
        return a.index < b.index;
    });
}

int main() {
    int n;
    cout << "Enter the numbe of Processor: ";
    cin >> n;
    vector<items> processor(n);
    for (int i = 0; i < n; i++) {
        processor[i].index = i;
        cout << "Enter processor name, arrival time and brust time: ";
        cin >> processor[i].name >> processor[i].at >> processor[i].bt;
    }
    firstComeFirstServe(processor);

    cout << "name\t at\t bt\t ct\t tat\t wt\n";
    for (auto it : processor) {
        cout << it.name << '\t' << it.at << '\t' << it.bt << '\t' <<
             it.ct << '\t' << it.tat << '\t' << it.wt << '\n';
    }
}
