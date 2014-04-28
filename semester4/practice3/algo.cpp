#include <cstdlib>
#include <iostream>

using namespace std;

int substitute(int value) {
  // The S-Box
  int s_Box[8192];

  // Populate s_Box with distinct values
  bool exists = false;
  int counter = 0;
  int tmp = 0;
  while (counter < 8192) {
      tmp = (int) rand() % 8192;
      exists = false;
      for (int i = 0; i < 8191; ++i) {
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
  return s_Box[value];
}

int main() {
  std::cout << substitute(20) << std::endl;
}
