#include <bits/stdc++.h>
using namespace std;

struct items{
    int id, size;
    string block_num = "N/A";
};

void worstFit(vector<items> &process, vector<int> &block) {
    for (int i = 0; i < process.size(); i++) {
        int pos = 0, mn = INT_MIN;
        bool check = false;
        for (int j = 0; j < block.size(); j++) {
            if (process[i].size <= block[j]) {
                if (block[j] - process[i].size > mn) {
                    mn = block[j] - process[i].size;
                    pos = j;
                    check = true;
                }
            }
        }
        if (check) {
            process[i].block_num = to_string(pos + 1);
            block[pos] -= process[i].size;
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

    worstFit(process, block);

    cout << "Process ID\t Process Size\t Block Number\n";
    for(int i = 0; i < process.size(); i++) {
        cout << process[i].id << "\t\t" << process[i].size << "\t\t" << process[i].block_num << '\n';
    }
}
