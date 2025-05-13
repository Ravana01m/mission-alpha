#include <iostream>
#include <vector>
using namespace std;
#define vvi vector<vector<int>>
#define vi vector<int>
bool isSafe(vi available, vvi max_need, 
            vvi allocated, int n_processes, int n_resources) {
    vvi need(n_processes, vi(n_resources));
    for (int i = 0; i < n_processes; i++)
        for (int j = 0; j < n_resources; j++)
            need[i][j] = max_need[i][j] - allocated[i][j];

    vector<bool> finished(n_processes, false);
    vi safe_sequence;
    int count = 0;

    while (count < n_processes) {
        bool found = false;
        for (int p = 0; p < n_processes; p++) {
            if (!finished[p]) {
                bool can_allocate = true;
                for (int r = 0; r < n_resources; r++) {
                    if (need[p][r] > available[r]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int r = 0; r < n_resources; r++)
                        available[r] += allocated[p][r];
                    safe_sequence.push_back(p);
                    finished[p] = true;
                    count++;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "System is not in safe state\n";
            return false;
        }
    }
    cout << "System is in safe state. Safe sequence: ";
    for (int p : safe_sequence) cout << "P" << p << " ";
    cout << endl;
    return true;
}
int main() {
    cout<<"No of Processes: ";
    int n_processes, n_resources;
    cin>>n_processes;
    cout<<"No of type of resources : ";
    cin>>n_resources;
    vi available(n_resources);
    for(int i = 0; i < n_resources; i++) {
        cout << "Enter available resources of type " << i + 1 << ": ";
        cin >> available[i];
    }
    vvi max_need(n_processes, vi(n_resources));
    for (int i = 0; i < n_processes; i++) {
        cout << "Enter max need of process " << i + 1 << ": ";
        for (int j = 0; j < n_resources; j++)
            cin >> max_need[i][j];
    }
    vvi allocated(n_processes, vi(n_resources));
    for (int i = 0; i < n_processes; i++) {
        cout << "Enter allocated resources of process " << i + 1 << ": ";
        for (int j = 0; j < n_resources; j++)
            cin >> allocated[i][j];
    }
    isSafe(available, max_need, allocated, n_processes, n_resources);
}