#include <bits/stdc++.h>

using namespace std;

struct Partition {
    int id;
    int size;
    bool allocated;
};

void bestFit(vector<Partition>& partitions, int processSize) {
    int bestFitIdx = -1;

    for (int i = 0; i < partitions.size(); ++i) {
        if (!partitions[i].allocated && partitions[i].size >= processSize) {
            if (bestFitIdx == -1 || partitions[i].size < partitions[bestFitIdx].size) {
                bestFitIdx = i;
            }
        }
    }

    if (bestFitIdx != -1) {
        partitions[bestFitIdx].allocated = true;
        cout << "Process allocated to Partition " << partitions[bestFitIdx].id << endl;
    } else {
        cout << "No suitable partition found for the process." << endl;
    }
}

int main() {
    int numPartitions, numProcesses;

    cout << "Enter the number of partitions: ";
    cin >> numPartitions;

    vector<Partition> partitions(numPartitions);

    for (int i = 0; i < numPartitions; ++i) {
        partitions[i].id = i + 1;
        cout << "Enter the size of Partition " << partitions[i].id << ": ";
        cin >> partitions[i].size;
        partitions[i].allocated = false;
    }

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    for (int i = 0; i < numProcesses; ++i) {
        int processSize;
        cout << "Enter the size of Process " << i + 1 << ": ";
        cin >> processSize;
        bestFit(partitions, processSize);
    }

    return 0;
}
