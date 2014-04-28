#include <cstdlib>
#include <iostream>

using namespace std;

char substituteChar(char value) {
  // The S-Box
  size_t size = 128;
  int sBox[size];

  // Populate sBox with distinct values
  bool exists = false;
  int counter = 0;
  int tmp = 0;
  while (counter < size) {
      tmp = (int) rand() % size;
      exists = false;
      for (int i = 0; i < size - 1; ++i) {
          if (sBox[i] == tmp) {
              exists = true;
              break;
          }
      }
      if (!exists) {
          sBox[counter] = tmp;
          counter++;
      }
  }

  // Get the substitution
  return (char) sBox[(int) value];
}

string substituteString(string value) {
  string result;
  char tmp;

  for (size_t i = 0; i < value.size(); ++i) {
    tmp = substituteChar(value[i]);
    result.append(&tmp);
  }

  return result;
}

int main() {
  std::cout << substituteChar('b') << std::endl;
  std::cout << substituteString("Test") << std::endl;
}
