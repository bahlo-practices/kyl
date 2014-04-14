/*
 * File:   main.cpp
 * Author: Yvonne, Frederik & Arne
 *
 * Created on 8. April 2014, 17:52
 */

#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

void permutation() {
    int x[128];  // Clear text
    int y[128];  // Result
    int pi[128]; // Bijection

    // Populate x
    for (int i = 0; i < 128; i++) {
        x[i] = i + 1;
    }

    // Populate pi with distinct values
    bool exists = false;
    int counter = 0;
    int tmp = 0;
    while (counter < 127) {
        tmp = (int) rand() % 128;
        exists = false;
        for (int i = 0; i < 128; i++) {
            if (pi[i] == tmp) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            pi[counter] = tmp;
            counter++;
        }
    }

    // Populate y with the final values
    for (int i = 0; i < 128; i++) {
        y[i] = x[pi[i]];
    }

    // Cout
    for (int i = 0; i < 128; i++) {
        cout << "x = " << x[i] << "\t\tpi = " << pi[i] << "\t\ty = " << y[i] << endl;
    }
}

void substitution() {
    int x1 = 1234;
    int x2 = 5678;
    int x3 = 6666;
    int y1 = 0;
    int y2 = 0;
    int y3 = 0;

    // The S-Box
    int s_Box[8192];

    // Populate s_Box with distinct values
    bool exists = false;
    int counter = 0;
    int tmp = 0;
    while (counter < 8191) {
        tmp = (int) rand() % 8192;
        exists = false;
        for (int i = 0; i < 8192; i++) {
            if (s_Box[i] == tmp) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            s_Box[counter] = tmp;
            counter++;
        }
    }

    // Get the substitution
    y1 = s_Box[x1];
    y2 = s_Box[x2];
    y3 = s_Box[x3];

    cout << "Klartext 1: "<< x1 << "\tSubstitution: " << y1 << endl;
    cout << "Klartext 2: "<< x2 << "\tSubstitution: " << y2 << endl;
    cout << "Klartext 3: "<< x3 << "\tSubstitution: " << y3 << endl;
}

int main() {
    srand(time(NULL));
    permutation();
    //substitution();
    return 0;
}
