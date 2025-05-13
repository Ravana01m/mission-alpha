#include<bits/stdc++.h>
using namespace std;

int main() {
    cout<<"Enter the no of processes: ";
    int n; cin >> n;
    vector<array<int,3>> in(n), out(n);
    vector<int> priority(n);
    for(int i = 0, x, y; i < n; i++) {
        cout << "Enter Arrival and Burst time of Process"<<i+1<<" : ";
        cin>>x>> y, in[i] = {x, i, y};
    }
    for(int i = 0; i < n; i++) {
        cout << "Enter Priority of Process "<<i+1<<": ";
        cin>>priority[i];
    }
    sort(in.begin(), in.end());
    int t = 0, i = 0;
    priority_queue<array<int,5>, vector<array<int,5>>, greater<>> pq;
    while(i < n || !pq.empty()) {
        if(pq.empty()) t = max(in[i][0], t);
        while(i < n && in[i][0] <= t) pq.push({priority[in[i][1]], in[i][0], in[i][1], in[i][2], in[i][2]}), i++;
        auto [prior, at, id, bt, dur] = pq.top(); pq.pop();
        int nxt = (i < n) ? in[i][0] : 1e9;
        if(nxt - t <= dur) {
            if(nxt - t < dur) pq.push({prior, at, id, bt, dur - (nxt - t)});
            else out[id] = {nxt, nxt - at, nxt - at - bt};
            t = nxt;
        } else {
            t += dur;
            out[id] = {t, t - at, t - at - bt};
        }
    }
    cout << "Process\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for(int i = 0; i < n; i++)
        cout << "P" << i + 1 << "\t" << out[i][0] << "\t\t" << out[i][1] << "\t\t" << out[i][2] << '\n';
}