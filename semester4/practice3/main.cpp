#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <vector>

#include "aes.h"

using namespace std;

const string key = "12345789";

void fillRow(aes::row &r) {
  for (size_t i = r.size(); i < 4; ++i) {
    r.push_back(0);
  }
}

void fillBlock(aes::block &b) {
  for (size_t i = b.size(); i < 4; i++) {
    aes::row r;
    fillRow(r);
    b.push_back(r);
  }
}

void printBlocks(const vector<aes::block> blocks) {
  for (size_t i = 0; i < blocks.size(); i++) { // Blocks
    for (size_t j = 0; j < blocks.at(i).size(); j++) { // Block
      for (size_t k = 0; k < blocks.at(i).at(j).size(); k++) { // Row
        cout << setw(3) << left << hex << blocks.at(i).at(j).at(k);
      }
      cout << endl;
    }
    cout << endl;
  }
}

vector<aes::block> getBlocks(string message) {
  vector<aes::block> blocks;
  const char *cmsg = message.c_str();

  aes::block b;
  aes::row r;
  for (size_t i = 0; i < message.size(); ++i) {
    int charCode = (int) cmsg[i];

    r.push_back(charCode);
    if ((i + 1) % 4 == 0) {
      b.push_back(r);

      vector<int> tmp;
      r = tmp;
    }
    if ((i + 1) % 16 == 0) {
      // Create new b
      blocks.push_back(b);

      vector<vector<int> > tmp;
      b = tmp;
    }

  }

  // Fill last row with zeros
  if (r.size() > 0) {
    fillRow(r);
    b.push_back(r);
  }

  // Fill last block with rows
  if (b.size() > 0) {
    fillBlock(b);
    blocks.push_back(b);
  }

  return blocks;
}

int main() {
  string message = "";

  cout << "Nachricht: ";
  getline(cin, message);

  cout << endl << "getBlocks.." << endl << endl;
  vector<aes::block> blocks = getBlocks(message);
  printBlocks(blocks);

  cout << endl << "subBytes.." << endl << endl;
  for (size_t i = 0; i < blocks.size(); ++i) {
    aes::subBytes(blocks.at(i));
  }
  printBlocks(blocks);

  cout << endl << "shiftRows.." << endl << endl;
  for (size_t i = 0; i < blocks.size(); ++i) {
    aes::shiftRows(blocks.at(i));
  }
  printBlocks(blocks);

  return 0;
}
