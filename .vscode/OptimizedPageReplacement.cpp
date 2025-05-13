#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;
int findPageToReplace(const vector<int>& memory, const vector<int>& pageSequence, int startIndex) {
    int farthest = startIndex;
    int indexToReplace = -1;

    for (int i = 0; i < memory.size(); i++) {
        int currentPage = memory[i];
        int j;
        for (j = startIndex; j < pageSequence.size(); j++) {
            if (currentPage == pageSequence[j]) {
                if (j > farthest) {
                    farthest = j;
                    indexToReplace = i;
                }
                break;
            }
        }
        if (j == pageSequence.size()) {
            // Page not found in future, replace this
            return i;
        }
    }
    return (indexToReplace == -1) ? 0 : indexToReplace;
}

int main() {
    int frames, pages;

    cout << "Enter number of frames: ";
    cin >> frames;

    cout << "Enter number of pages: ";
    cin >> pages;

    vector<int> pageSequence(pages);
    cout << "Enter the page reference string (space separated): ";
    for (int i = 0; i < pages; i++) {
        cin >> pageSequence[i];
    }

    vector<int> memory;
    int pageFaults = 0;

    cout << "\nPage Replacement Process:\n";
    for (int i = 0; i < pages; i++) {
        int page = pageSequence[i];
        auto it = find(memory.begin(), memory.end(), page);

        if (it == memory.end()) {
            if (memory.size() == frames) {
                int indexToReplace = findPageToReplace(memory, pageSequence, i + 1);
                memory[indexToReplace] = page;
            } else {
                memory.push_back(page);
            }
            pageFaults++;
            
            cout << "Page " << page << " caused a fault. Frames: [";
            for (size_t j = 0; j < memory.size(); j++) {
                cout << memory[j];
                if (j != memory.size() - 1) cout << " ";
            }
            cout << "]" << endl;
        } else {
            cout << "Page " << page << " accessed (no fault). Frames: [";
            for (size_t j = 0; j < memory.size(); j++) {
                cout << memory[j];
                if (j != memory.size() - 1) cout << " ";
            }
            cout << "]" << endl;
        }
    }

    cout << "\nTotal Page Faults: " << pageFaults << endl;

    return 0;
}