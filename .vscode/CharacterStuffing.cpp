#include<bits/stdc++.h>

using namespace std;

string characterStuffing(string& data, string& flag, string& escape) {
    string stuffed;
    int i = 0;
    while (i < data.length()) {
        if (data.substr(i, flag.length()) == flag) {
            stuffed += escape + flag;
            i += flag.length();
        } else if (data.substr(i, escape.length()) == escape) {
            stuffed += escape + escape;
            i += escape.length();
        } else {
            stuffed += data[i];
            ++i;
        }
    }
    return flag + stuffed + flag;
}

int main() {
    string data, flag, escape;
    cout << "Enter data: ";
    cin>>data;
    cout << "Enter flag sequence: ";
    cin>>flag;
    cout << "Enter escape sequence: ";
    cin>>escape;
    string result = characterStuffing(data, flag, escape);
    cout << "Stuffed Data: " << result << endl;
}
