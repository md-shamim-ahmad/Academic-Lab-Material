#include <bits/stdc++.h>
using namespace std;

// Function to check if a process can be granted the requested resources
bool isSafe( vector<vector<int>>& maxMatrix, vector<vector<int>>& allocationMatrix,
             vector<int>& available, int process,  vector<int>& request) {
    int numResources = available.size();
    vector<int> work = available;
    vector<bool> finish(maxMatrix.size(), false);

    // Step 1: Check if the requested resources are less than or equal to the needs
    for (int i = 0; i < numResources; ++i) {
        if (request[i] > maxMatrix[process][i] - allocationMatrix[process][i]) {
            return false;
        }
    }

    // Step 2: Temporarily allocate the requested resources and check for safety
    for (int i = 0; i < numResources; ++i) {
        work[i] -= request[i];
        allocationMatrix[process][i] += request[i];
    }

    int numProcesses = maxMatrix.size();
    int numFinished = 0;
    while (numFinished < numProcesses) {
        bool found = false;
        for (int i = 0; i < numProcesses; ++i) {
            if (!finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < numResources; ++j) {
                    if (maxMatrix[i][j] - allocationMatrix[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute) {
                    finish[i] = true;
                    for (int j = 0; j < numResources; ++j) {
                        work[j] += allocationMatrix[i][j];
                    }
                    found = true;
                    ++numFinished;
                }
            }
        }
        if (!found) {
            for (int i = 0; i < numResources; ++i) {
                work[i] += request[i];
                allocationMatrix[process][i] -= request[i];
            }
            return false;
        }
    }

    return true;
}

// Banker's algorithm function to handle resource requests
bool bankerAlgorithm(vector<vector<int>>& maxMatrix, vector<vector<int>>& allocationMatrix,
                     vector<int>& available, int process,  vector<int>& request) {
    if (!isSafe(maxMatrix, allocationMatrix, available, process, request)) {
        cout << "Request denied. Not in a safe state." << endl;
        return false;
    }

    // Request is safe, allocate the resources to the process
    int numResources = available.size();
    for (int i = 0; i < numResources; ++i) {
        available[i] -= request[i];
        allocationMatrix[process][i] += request[i];
        maxMatrix[process][i] -= request[i];
    }

    cout << "Request granted. Allocation Matrix:" << endl;
    for ( auto& row : allocationMatrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return true;
}

int main() {
    int numProcesses, numResources;

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    cout << "Enter the number of resources: ";
    cin >> numResources;

    vector<vector<int>> maxMatrix(numProcesses, vector<int>(numResources));
    vector<vector<int>> allocationMatrix(numProcesses, vector<int>(numResources));
    vector<int> available(numResources);

    cout << "Enter the maximum resource matrix:" << endl;
    for (int i = 0; i < numProcesses; ++i) {
        for (int j = 0; j < numResources; ++j) {
            cin >> maxMatrix[i][j];
        }
    }

    cout << "Enter the allocation matrix:" << endl;
    for (int i = 0; i < numProcesses; ++i) {
        for (int j = 0; j < numResources; ++j) {
            cin >> allocationMatrix[i][j];
            available[j] -= allocationMatrix[i][j];
        }
    }

    for (int i = 0; i < numResources; ++i) {
        cin >> available[i];
        available[i] += available[i]; // Calculate total available resources
    }

    int process;
    cout << "Enter the process number requesting resources: ";
    cin >> process;

    vector<int> request(numResources);
    cout << "Enter the request vector for process " << process << ": ";
    for (int i = 0; i < numResources; ++i) {
        cin >> request[i];
    }

    bankerAlgorithm(maxMatrix, allocationMatrix, available, process, request);

    return 0;
}
