#include<bits/stdc++.h>
using namespace std;

int main() {
    cout<<"Enter no of Processes: ";
    int n, t = 0, i = 0;
    cin>>n;
    vector<array<int,3>> info(n), ans(n);
    vector<int>priority(n);
    for(int i = 0, x, y; i < n; i++) {
        cout<<"Enter Arrival and Burst time of Process "<<i+1<<": ";
        cin>>x>>y;
        info[i] = {x, i, y};
    }
    for(int i = 0; i < n; i++) {
        cout<<"Enter Priority of Process "<<i+1<<": ";
        cin>>priority[i];
    }
    sort(info.begin(), info.end());
    priority_queue<array<int,4>, vector<array<int,4>>, greater<>> pq;
    while(i < n || !pq.empty()) {
        if(pq.empty()) t = max(info[i][0], t);
        while(i < n && info[i][0] <= t) pq.push({priority[info[i][1]], info[i][0], info[i][1], info[i][2]}), i++;
        auto [pr, at, id, bt] = pq.top(); pq.pop();
        t += bt;
        ans[id] = {t, t - at, t - at - bt};
    }
    cout<<"Process\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for(int i = 0; i < n; i++)
        cout<<i+1<<"\t"<<ans[i][0]<<"\t\t"<<ans[i][1]<<"\t\t"<<ans[i][2]<<"\n";



}