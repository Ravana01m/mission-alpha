#include<bits/stdc++.h>
using namespace std;

string bitStuff(string data, int n) {
    string stuffedData = "";
    int count = 0;
    for (char bit : data) {
        stuffedData += bit;
        if (bit == '1') {
            count++;
            if (count == n) {
                stuffedData += '0';
                count = 0;
            }
        } else count = 0;
    }
    return stuffedData;
}

int main() {
    cout<<"Enter the data bits: ";
    string data;
    cin>>data;
    cout<<"Enter no of Consecutive 1's after 0 is stuffed: ";
    int n;
    cin>>n;
    string stuffData = bitStuff(data, n);
    cout<<"Data after bit stuffing: "<<stuffData<<endl;
}