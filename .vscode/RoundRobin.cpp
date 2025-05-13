#include<bits/stdc++.h>
using namespace std;

int main() {
    int n,tq,t = 0, ptr = 0;
    cout << "No of Processes : ";
    cin >> n;
    vector<array<int, 3>> info(n), ans(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival and Burst time of Process" << i + 1 << " : ";
        int x, y;
        cin >> x >> y;
        info[i] = {x, i, y};
    }
    cout << "Enter Time Quantum : ";
    cin >> tq;
    queue<array<int, 3>> q;
    sort(info.begin(), info.end());
    while (ptr < n || !q.empty()) {
        if (q.empty()) t = max(t, info[ptr][0]);
        while (ptr < n && info[ptr][0] <= t) q.push({info[ptr][2], info[ptr][1], info[ptr++][0]});
        auto temp = q.front();
        q.pop();
        int bt = temp[0], pid = temp[1], at = temp[2];
        t += min(bt, tq);
        while (ptr < n && info[ptr][0] <= t) 
            q.push({info[ptr][2], info[ptr][1], info[ptr++][0]});
        if (bt > tq) {
            bt -= tq;
            q.push({bt, pid, at});
        } else {
            ans[pid][0] = t; // Completion time
            ans[pid][1] = t - at; // Turnaround time = Completion time - Arrival time
            ans[pid][2] = ans[pid][1] - info[pid][2]; // Waiting time = Turnaround time - Burst time
        }
    }
    cout << "Process\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++)
        cout << "P" << i + 1 << "\t" << ans[i][0] << "\t\t" << ans[i][1] << "\t\t" << ans[i][2] << '\n';

}