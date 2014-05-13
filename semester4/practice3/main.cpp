#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <vector>

#include "aes.h"

using namespace std;

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

void printBlock(const aes::block block) {
  // Each Row
  for (size_t j = 0; j < block.size(); j++) { // Block
    for (size_t k = 0; k < block.at(j).size(); k++) {
      cout << setw(4) << left << hex << block.at(j).at(k) << dec;
    }
    cout << endl;
  }
}

void printBlocks(const vector<aes::block> blocks) {
  for (size_t i = 0; i < blocks.size(); i++) { // Blocks
    printBlock(blocks.at(i));
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

      aes::row tmp;
      r = tmp;
    }
    if ((i + 1) % 16 == 0) {
      // Create new b
      blocks.push_back(b);

      aes::block tmp;
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

aes::block getKey(string k) {
  const char *c = k.c_str();
  aes::block b;
  aes::row r;

  for (size_t i = 0; i < sizeof(c); ++i) {
    r.push_back((int) c[i]);

    if ((i + 1) % 4 == 0) {
      b.push_back(r);

      aes::row tmp;
      r = tmp;
    }
  }

  return b;
}

int main() {
  string message = "";
  string keyString = "";

  cout << "Nachricht: ";
  getline(cin, message);

  cout << "Key: ";
  getline(cin, keyString);

  cout << endl << "getKey.."  << endl << endl;
  aes::block key = getKey(keyString);
  fillBlock(key); // Fill with zeros
  printBlock(key);

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

  cout << endl << "transformate.." << endl << endl;
  vector<aes::block> columned;
  for (size_t i = 0; i < blocks.size(); ++i) {
    columned.push_back(aes::transformate(blocks.at(i)));
  }
  printBlocks(columned);

  cout << endl << "transformate#2.." << endl << endl;
  vector<aes::block> rowed;
  for (size_t i = 0; i < columned.size(); ++i) {
    rowed.push_back(aes::transformate(columned.at(i)));
  }
  printBlocks(rowed);

  cout << endl << "mixColumns.." << endl << endl;
  for (size_t i = 0; i < blocks.size(); ++i) {
    aes::mixColumns(blocks.at(i));
  }
  printBlocks(blocks);

  cout << endl << "hash.." << endl << endl;
  cout << aes::hash(blocks, key) << endl << endl;

  return 0;
}
