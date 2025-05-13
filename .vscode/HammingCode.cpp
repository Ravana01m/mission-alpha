#include <iostream>
#include <vector>
using namespace std;

int redundantBits(int dataBits) {
    int r = 0;
    while ((1 << r) < (dataBits + r + 1)) {
        r++;
    }
    return r;
}

vector<int> generateHammingCode(vector<int> data) {
    int m = data.size();
    int r = redundantBits(m);
    int totalBits = m + r;
    vector<int> hammingCode(totalBits, 0);

    // Positioning data bits
    int j = 0;
    for (int i = 0; i < totalBits; i++) {
        if (((i + 1) & i) == 0) { // Check if (i+1) is a power of two (0-based parity positions)
            continue;
        }
        hammingCode[i] = data[j];
        j++;
    }

    // Calculating parity bits
    for (int i = 0; i < r; i++) {
        int parityIndex = (1 << i) - 1; // 2^i -1 (0-based)
        int parity = 0;
        for (int k = parityIndex; k < totalBits; k += 2 * (parityIndex + 1)) {
            for (int p = k; p < min(k + parityIndex + 1, totalBits); p++) {
                parity ^= hammingCode[p];
            }
        }
        hammingCode[parityIndex] = parity;
    }

    return hammingCode;
}

// Function to check for errors in received Hamming Code
int detectError(vector<int> receivedCode) {
    int totalBits = receivedCode.size();
    int r = 0;
    while ((1 << r) < (totalBits + 1)) {
        r++;
    }
    int errorPosition = 0;

    for (int i = 0; i < r; i++) {
        int parityIndex = (1 << i) - 1;
        int parity = 0;
        for (int k = parityIndex; k < totalBits; k += 2 * (parityIndex + 1)) {
            for (int p = k; p < min(k + parityIndex + 1, totalBits); p++) {
                parity ^= receivedCode[p];
            }
        }
        if (parity != 0) {
            errorPosition += (parityIndex + 1);
        }
    }

    return errorPosition;
}

int main() {
    int dataBits;
    cout << "Enter number of data bits: ";
    cin >> dataBits;
    
    vector<int> data(dataBits);
    cout << "Enter data bits one by one (0/1): ";
    for (int i = 0; i < dataBits; i++) {
        cin >> data[i];
    }
    
    vector<int> hammingCode = generateHammingCode(data);
    cout << "Hamming Code generated: ";
    for (int bit : hammingCode) {
        cout << bit << " ";
    }
    cout << endl;
    
    vector<int> receivedCode = hammingCode;
    cout << "Enter received Hamming Code (space-separated, " << hammingCode.size() << " bits): ";
    for (int i = 0; i < receivedCode.size(); i++) {
        cin >> receivedCode[i];
    }
    
    int errorPos = detectError(receivedCode);
    if (errorPos == 0) {
        cout << "No error detected!" << endl;
    } else {
        cout << "Error detected at position: " << errorPos << " (1-based)" << endl;
        receivedCode[errorPos - 1] ^= 1; // Correct the error
        cout << "Corrected Hamming Code: ";
        for (int bit : receivedCode) {
            cout << bit << " ";
        }
        cout << endl;
    }
    return 0;
}



#include <iostream>
#include <string>

int hammingDistance(const std::string& s1, const std::string& s2) {
    if (s1.length() != s2.length()) {
        std::cerr << "Error: Strings must be of equal length.\n";
        return -1;
    }

    int distance = 0;
    for (size_t i = 0; i < s1.length(); ++i) {
        if (s1[i] != s2[i]) {
            ++distance;
        }
    }
    return distance;
}

int main() {
    std::string str1 = "karolin";
    std::string str2 = "kathrin";

    int result = hammingDistance(str1, str2);
    if (result != -1) {
        std::cout << "Hamming distance: " << result << std::endl;
    }

    return 0;
}