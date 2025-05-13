#include<bits/stdc++.h>
using namespace std;
int main() {
    cout<<"Enter the data: ";
    string data;
    cin>>data;
    cout<<"Enter the CRC code: ";
    string crc;
    cin>>crc;
    string crcData = data + string(crc.size() - 1, '0');
    string xorCode = crcData.substr(0, crc.size()-1);
    for(int i = crc.size(); i < crcData.size(); i++) {
        xorCode += crcData[i];
        if(xorCode[0] == '1') {
            for(int j = 0; j < crc.size(); j++) xorCode[j] = (xorCode[j] == crc[j]) ? '0' : '1';
        } else {
            for(int j = 0; j < crc.size(); j++) xorCode[j] = (xorCode[j] == '0') ? '0' : '1';
        }
        xorCode = xorCode.substr(1);
    }
    cout<<"Transmitted Data: " << data + xorCode << endl;
}