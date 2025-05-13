#include<bits/stdc++.h>
using namespace std;

int main() {
    cout<<"Enter the no of processes: ";
    int n; cin >> n;
    vector<array<int,3>> in(n), out(n);
    for(int i = 0, x, y; i < n; i++) {
        cout << "Enter Arrival and Burst time of Process"<<i+1<<" : ";
        cin>>x>> y, in[i] = {x, i, y};
    }
    sort(in.begin(), in.end());
    int t = 0, i = 0;
    priority_queue<array<int,3>, vector<array<int,3>>, greater<>> pq;
    while(i < n || !pq.empty()) {
        if(pq.empty()) t = max(in[i][0], t);
        while(i < n && in[i][0] <= t) pq.push({in[i][2], in[i][1], in[i][0]}), i++;
        auto [dur, id, st] = pq.top(); pq.pop();
        t+=dur;
        out[id] = {t, t - st, t - st - dur};
    }
    cout << "Process\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for(int i = 0; i < n; i++)
        cout << "P" << i + 1 << "\t" << out[i][0] << "\t\t" << out[i][1] << "\t\t" << out[i][2] << '\n';
}