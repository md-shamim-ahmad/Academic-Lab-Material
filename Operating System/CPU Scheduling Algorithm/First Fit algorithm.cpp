// C++ program for the implementation of the First Fit algorithm
#include <bits/stdc++.h>
using namespace std;

class process {
public:
    size_t size;
    pid_t no;
};

class memory {
public:
    size_t size{};
    pid_t no{};
    queue<process> space_occupied;

    void push(const process p) {
        if (p.size <= size) {
            space_occupied.push(p);
            size -= p.size;
        }
    }

    process pop() {
        process p;
        if (!space_occupied.empty()) {
            p = space_occupied.front();
            space_occupied.pop();
            size += p.size;
            return p;
        }
    }

    bool empty() {
        return space_occupied.empty();
    }
};
vector<memory> first_fit(vector<memory> memory_blocks, queue<process> processess) {
    int i = 0;
    bool done, done1;
    memory na;
    na.no = -10;
    while (!processess.empty()) {
        done = 0;
        for (i = 0; i < memory_blocks.size(); i++) {
            done1 = 0;
            if (memory_blocks.at(i).size
                >= processess.front().size) {
                memory_blocks.at(i).push(processess.front());
                done = 1;
                done1 = 1;
                break;
            }
        }
        if (done == 0 && done1 == 0) {
            na.size += processess.front().size;
            na.push(processess.front());
        }
        processess.pop();
    }
    if (!na.space_occupied.empty())
        memory_blocks.push_back(na);
    return memory_blocks;
}

void display(vector<memory> memory_blocks) {
    int i = 0, temp = 0;
    process p{};
    cout << "+-------------+--------------+--------------+\n";
    cout << "| Process no. | Process size | Memory block |\n";
    cout << "+-------------+--------------+--------------+\n";

    for (i = 0; i < memory_blocks.size(); i++) {

        while (!memory_blocks.at(i).empty()) {
            p = memory_blocks.at(i).pop();
            temp = to_string(p.no).length();
            cout << "|" << string(7 - temp / 2 - temp % 2, ' ') << p.no << string(6 - temp / 2, ' ') << "|";
            temp = to_string(p.size).length();
            cout << string(7 - temp / 2 - temp % 2, ' ') << p.size << string(7 - temp / 2, ' ') << "|";
            temp = to_string(memory_blocks.at(i).no).length();
            cout << string(7 - temp / 2 - temp % 2, ' ');
            if (memory_blocks.at(i).no != -10)
                cout << memory_blocks.at(i).no;
            else
                cout << "N/A";
            cout << string(7 - temp / 2, ' ') << "|" << endl;
        }
    }
    cout << "+-------------+--------------+--------------+" << '\n';
}

int main()
{
    // Declare memory blocks
    vector<memory> memory_blocks(5);
    // Declare first fit blocks
    vector<memory> first_fit_blocks;
    // Declare queue of all processess
    queue<process> processess;
    process temp;

    // Set sample data
    memory_blocks[0].no = 1;
    memory_blocks[0].size = 400;

    memory_blocks[1].no = 2;
    memory_blocks[1].size = 500;

    memory_blocks[2].no = 3;
    memory_blocks[2].size = 300;

    memory_blocks[3].no = 4;
    memory_blocks[3].size = 200;

    memory_blocks[4].no = 5;
    memory_blocks[4].size = 100;

    temp.no = 1;
    temp.size = 88;

    // Push the process
    processess.push(temp);

    temp.no = 2;
    temp.size = 192;

    // Push the process
    processess.push(temp);

    temp.no = 3;
    temp.size = 277;

    // Push the process
    processess.push(temp);

    temp.no = 4;
    temp.size = 365;

    // Push the process
    processess.push(temp);

    temp.no = 5;
    temp.size = 489;

    // Push the process
    processess.push(temp);

    // Get the data
    first_fit_blocks = first_fit(memory_blocks, processess);

    // Display the data
    display(first_fit_blocks);
    memory_blocks.clear();
    memory_blocks.shrink_to_fit();
    first_fit_blocks.clear();
    first_fit_blocks.shrink_to_fit();
    return 0;
}
