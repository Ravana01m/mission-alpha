#include <bits/stdc++.h>
#include <chrono>
using namespace std;

void slidingWindowProtocol(string &bits, int n, int t) {
    queue<char> window;
    int i = 0;
    int sent = 0;
    
    while (i < bits.size()) {
        cout << "Sending: ";
        for (int j = 0; window.size() < n && sent < bits.size(); j++) {
            window.push(bits[sent]);
            cout << bits[sent] << " ";
            sent++;
        }
        cout << endl;
        this_thread::sleep_for(chrono::seconds(2));
        if(i==t) {
            cout << "Acknowledgement not received, Previous Bits Discarded. Resending : ";
            window = queue<char>();
            for(int j = 0; j < n && i+j < bits.size(); j++) {
                window.push(bits[i+j]);
                cout<<bits[i+j]<<" ";
            }
        }
        cout<<endl;
        if(sent == bits.size()) {
            cout << "Acknowledged "<< i+1<< " Bit. All bits sent."<< endl;
        }
        else cout << "Acknowledged "<< i+1<< " Bit. Sending next bit..."<< endl;
        window.pop();
        i++;
        cout << "--------------------------" << endl;
    }
}

int main() {
    srand(time(0));
    cout<<"Enter the data bits: ";
    string data;
    cin>>data;
    cout<<"Enter the window size: ";
    int n;
    cin>>n;
    int t = rand()%n;
    slidingWindowProtocol(data, n,t);
    return 0;
}
