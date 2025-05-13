#include<bits/stdc++.h>
using namespace std;

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
    sort(info.begin(), info.end());
    vector<array<int,3>>ans(n);
    int t = 0;
    for(int i = 0; i < n; i++) {
        if(t < info[i][0]) {
            t = info[i][0];
        }
        ans[info[i][1]][0] = t + info[i][2]; // Completion time
        ans[info[i][1]][1] = ans[info[i][1]][0] - info[i][0]; // Turnaround time = Completion time - Arrival time
        ans[info[i][1]][2] = ans[info[i][1]][1] - info[i][2]; // Waiting time = Turnaround time - Burst time
        t += info[i][2]; // Update current time
    }
    for(int i = 0; i < n; i++) {
        cout<<"Process "<<i+1<<": Completion Time = "<<ans[i][0]<<", Turnaround Time = "<<ans[i][1]<<", Waiting Time = "<<ans[i][2]<<endl;
    }

}