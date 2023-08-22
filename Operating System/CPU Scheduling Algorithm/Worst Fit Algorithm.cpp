#include <bits/stdc++.h>
using namespace std;

struct Partition {
    int id;
    int size;
    bool allocated;
};

void worstFit(vector<Partition>& partitions, int processSize) {
    int worstFitIdx = -1;

    for (int i = 0; i < partitions.size(); ++i) {
        if (!partitions[i].allocated && partitions[i].size >= processSize) {
            if (worstFitIdx == -1 || partitions[i].size > partitions[worstFitIdx].size) {
                worstFitIdx = i;
            }
        }
    }

    if (worstFitIdx != -1) {
        partitions[worstFitIdx].allocated = true;
        cout << "Process allocated to Partition " << partitions[worstFitIdx].id << endl;
    } else {
        cout << "No suitable partition found for the process." << endl;
    }
}

int main() {
    int numPartitions, numProcesses;

    cout << "Enter the number of partitions: ";
    cin >> numPartitions;

    vector<Partition> partitions(numPartitions);

    for (int i = 0; i < numPartitions; i++) {
        cout << "Enter the size of Partition " << i + 1 << ": ";
        cin >> partitions[i].size;
        partitions[i].id = i + 1;
        partitions[i].allocated = false;
    }

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    for (int i = 0; i < numProcesses; ++i) {
        int processSize;
        cout << "Enter the size of Process " << i + 1 << ": ";
        cin >> processSize;
        worstFit(partitions, processSize);
    }
    return 0;
}
