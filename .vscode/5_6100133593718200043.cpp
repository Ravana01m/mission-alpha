#include<bits/stdc++.h>
using namespace std;

vector<array<int,3>>FCFS(vector<array<int,3>>&info) {
    int n = info.size();
    sort(info.begin(), info.end());
    vector<array<int,3>>ans(n);
    int t = 0;
    for(int i = 0; i < n; i++) {
        if(t < info[i][0]) {
            t = info[i][0];
        }
        ans[info[i][1]][0] = t + info[i][2]; 
        ans[info[i][1]][1] = ans[info[i][1]][0] - info[i][0];
        ans[info[i][1]][2] = ans[info[i][1]][1] - info[i][2];
        t += info[i][2];
    }
    return ans;
}

vector<array<int,3>>SJF(vector<array<int,3>>&in) {
    int n = in.size();
    sort(in.begin(), in.end());
    int t = 0, i = 0;
    vector<array<int,3>>out(n);
    priority_queue<array<int,3>, vector<array<int,3>>, greater<>> pq;
    while(i < n || !pq.empty()) {
        if(pq.empty()) t = max(in[i][0], t);
        while(i < n && in[i][0] <= t) pq.push({in[i][2], in[i][1], in[i][0]}), i++;
        auto [dur, id, st] = pq.top(); pq.pop();
        t+=dur;
        out[id] = {t, t - st, t - st - dur};
    }
    return out;
}

vector<array<int,3>>SRTF(vector<array<int,3>>&in) {
    int n = in.size();
    sort(in.begin(), in.end());
    int t = 0, i = 0;
    vector<array<int,3>>out(n);
    priority_queue<array<int,4>, vector<array<int,4>>, greater<>> pq;
    while(i < n || !pq.empty()) {
        if(pq.empty()) t = max(in[i][0], t);
        while(i < n && in[i][0] <= t) pq.push({in[i][2], in[i][1], in[i][0], in[i][2]}), i++;
        auto [dur, id, st, bt] = pq.top(); pq.pop();
        int nxt = (i < n) ? in[i][0] : 1e9;
        if(nxt - t <= dur) {
            if(nxt - t < dur) pq.push({dur - (nxt - t), id, st, bt});
            else out[id] = {nxt, nxt - st, nxt - st - bt};
            t = nxt;
        } else {
            t += dur;
            out[id] = {t, t - st, t - st - bt};
        }
    }
    return out;
}


vector<array<int,3>>PriorityScheduling(vector<array<int,3>>&in) {
    int n = in.size();
    vector<int>priority(n);
    for(int i = 0; i < n; i++) {
        cout<<"Enter Priority for Process"<<i+1<<": ";
        cin>>priority[i];
    }
    vector<array<int,3>>out(n);
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
    return out;
}

int main() {
    cout<<"No of Processes : ";
    int n;
    cin>>n;
    vector<array<int,3>>info(n);
    for(int i = 0; i < n; i++) {
        cout<<"Enter Arrival and Burst time of Process"<<i+1<<" : ";
        int x,y;
        cin>>x>>y;
        info[i] = {x,i,y};
    }
    cout<<"Press 1 for FCFS, 2 for SJF, 3 for SRTF, 4 for Priority Based Scheduling: ";
    int p;
    cin>>p;
    vector<array<int,3>>ans(n);
    if(p==1) ans = FCFS(info);
    if(p==2) ans = SJF(info);
    if(p==3) ans = SRTF(info);
    if(p==4) ans = PriorityScheduling(info);
    for(int i = 0; i < n; i++) {
        cout<<"Process "<<i+1<<": Completion Time = "<<ans[i][0]<<", Turnaround Time = "<<ans[i][1]<<", Waiting Time = "<<ans[i][2]<<endl;
    }

}









