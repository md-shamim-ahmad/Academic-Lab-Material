#include <bits/stdc++.h>
using namespace std;

struct items{
    int id, size;
    string block_num = "N/A";
};

void firstFit(vector<items> &process, vector<int> &block) {
    for (int i = 0; i < process.size(); i++) {
        for (int j = 0; j < block.size(); j++) {
            if (process[i].size <= block[j]) {
                process[i].block_num = to_string(j+1);
                block[j] -= process[i].size;
                break;
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of process: ";
    cin >> n;
    vector<items> process(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter size of the process: ";
        cin >> process[i].size;
        process[i].id = i + 1;
    }
    cout << "Enter number of block: ";
    cin >> n;
    vector<int> block(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter size of the block: ";
        cin >> block[i];
    }
    
    firstFit(process, block);

    cout << "Process ID\t Process Size\t Block Number\n";
    for(int i = 0; i < process.size(); i++) {
        cout << process[i].id << "\t\t" << process[i].size << "\t\t" << process[i].block_num << '\n';
    }
}
