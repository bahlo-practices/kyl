/*
 * File:   main.cpp
 * Author: Yvonne & Frederik
 *
 * Created on 8. April 2014, 17:52
 */

#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

void permutation() {
    int x[128];
    int y[128];
    int pi[128];
    for (int i = 0; i < 128; i++) {
        x[i] = i + 1;
    }
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
    for (int i = 0; i < 128; i++) {
        y[i] = x[pi[i]];
    }
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
    int s_Box[8192];

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

    y1 = s_Box[x1];
    y2 = s_Box[x2];
    y3 = s_Box[x3];

    cout << "Klartext 1: "<< x1 << "\tSubstitution: " << y1 << endl;
    cout << "Klartext 2: "<< x2 << "\tSubstitution: " << y2 << endl;
    cout << "Klartext 3: "<< x3 << "\tSubstitution: " << y3 << endl;
}

int main() {
    srand(time(NULL));
//    permutation();
    substitution();
    return 0;
}
