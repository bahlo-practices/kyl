#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

char substituteChar(char value, string key) {
  // Get the substitution
  return key[value];
}

string substituteString(string value, string key) {
  string result;
  char tmp;

  for (size_t i = 0; i < value.size(); ++i) {
    tmp = substituteChar(value[i], key);
    result.append(&tmp);
  }

  return result;
}

int main() {
  srand(time(NULL));

  // Generate key
  int i = 0;
  int tmp = 0;
  size_t size = 128;
  string key;
  while (i < size) {
      tmp = (int) rand() % size;
      char c = (char) tmp;
      key.append(&c);
      i++;
  }

  cout << "'" << substituteChar('b', key) << "'" << endl;
  cout << "'" << substituteString("Hier los", key) << "'"  << endl;

  // Create block
  vector<vector<string> > block;
}
