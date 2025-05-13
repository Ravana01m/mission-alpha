#include <iostream>
using namespace std;

int main() {
    int a[100], b[100], i, n, z, f, j, pf = 0, h = 0, temp;

    cout << "Enter the no. of pages: ";
    cin >> n;

    cout << "Enter the size of frame: ";
    cin >> f;

    cout << "Enter the pages value:\n";
    for (i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (i = 0; i < f; i++) {
        b[i] = -1;
    }

    i = 0;
    while (i < n) {
        if (b[i] == -1 && i < f) {
            b[i] = a[i];
            pf++;
        } else {
            z = 0;
            for (j = 0; j < f; j++) {
                if (b[j] == a[i]) {
                    h++;
                } else {
                    z++;
                }
            }
            if (z == f) {
                pf++;
                for (j = 0; j < f - 1; j++) {
                    temp = b[j];
                    b[j] = b[j + 1];
                    b[j + 1] = temp;
                }
                b[f - 1] = a[i];
            }
        }

        cout << "Current Frame: ";
        for (int k = 0; k < f; k++) {
            cout << b[k] << "\t";
        }
        cout << endl;

        i++;
    }

    cout << "Frame at the end:\n";
    for (i = 0; i < f; i++) {
        cout << "b[" << i << "] = " << b[i] << endl;
    }

    cout << "Page Fault = " << pf << endl;
    cout << "Hit = " << h << endl;

    return 0;
}
