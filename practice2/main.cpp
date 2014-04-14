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
    int x[128];  // Clear text
    int y[128];  // Result
    int pi[128]; // Result of bijection

    // Populate x
    for (int i = 0; i < 128; ++i) {
        x[i] = i + 1;
    }

    // Populate pi with distinct values
    for (int i = 0;i < 127;++i) {
      int tmp = (int) rand() % 128;

      // Find tmp in pi[] and break if it's in it
      for (int j = 0; j < 128; ++j) {
        if (pi[i] == tmp) {
          break;
        }
      }

      // Value not found, set a new one
      pi[i] = tmp;
    }

    // Populate y, the result, with the values in x at pi[i]
    for (int i = 0; i < 128; ++i) {
        y[i] = x[pi[i]];
    }

    // Print
    for (int i = 0; i < 128; i++) {
        cout << "x = " << x[i] << "\t\tpi = " << pi[i] << "\t\ty = " << y[i] << endl;
    }

    return;
}

int substitution(int value) {
    int sBox[8192];

    for (int i = 0;i < 8192;++i) {
      int tmp = (int) rand() % 8192;

      // Check if tmp is existant in sBox[i]
      for (int j = 0; j < 8192; ++j) {
        if (sBox[i] == tmp) {
          break;
        }
      }

      // tmp not found, set it at sBox[i]
      sBox[i] = tmp;
    }

    int result = sBox[value];

    cout << "Klartext: "<< value << "\tSubstitution: " << result << endl;
    return result;
}

int main() {
    srand(time(NULL));
    //permutation();
    substitution(1234);
    substitution(5678);
    substitution(6666);
    return 0;
}
