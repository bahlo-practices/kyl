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

void printBlocks(const vector<aes::block> blocks) {
  for (size_t i = 0; i < blocks.size(); i++) { // Blocks
    for (size_t j = 0; j < blocks.at(i).size(); j++) { // Block
      for (size_t k = 0; k < blocks.at(i).at(j).size(); k++) { // Row
        cout << setw(4) << left << hex << blocks.at(i).at(j).at(k) << dec;
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

aes::key getKey(const string sk) {
  aes::key k;

  for (int i = 0; i < sk.size(); ++i) {
    k.push_back((int) sk[i]);
  }

  return k;
}

void printKey(const aes::key k) {
  for (int i = 0; i < k.size(); ++i) {
    cout << setw(4) << left << hex << k.at(i) << dec;

    if ((i + 1) % 4 == 0) cout << endl;
  }
  cout << endl;
}

int main() {
  string message = "";
  string keyString = "";

  cout << "Nachricht: ";
  getline(cin, message);

  cout << "Key: ";
  getline(cin, keyString);

  cout << endl << "getKey.."  << endl << endl;
  aes::key key = getKey(keyString);
  printKey(key);

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

  cout << endl << "textMixColumns.." << endl << endl;
  vector<aes::block> testBlocks;
  aes::block testBlock;
  aes::column testColumn;
  testColumn.push_back(0xD4);
  testColumn.push_back(0xE0);
  testColumn.push_back(0xB8);
  testColumn.push_back(0x1E);
  testBlock.push_back(testColumn);
  testColumn.at(0) = 0xBF;
  testColumn.at(1) = 0xB4;
  testColumn.at(2) = 0x41;
  testColumn.at(3) = 0x27;
  testBlock.push_back(testColumn);
  testColumn.at(0) = 0x5D;
  testColumn.at(1) = 0x52;
  testColumn.at(2) = 0x11;
  testColumn.at(3) = 0x98;
  testBlock.push_back(testColumn);
  testColumn.at(0) = 0x30;
  testColumn.at(1) = 0xAE;
  testColumn.at(2) = 0xF1;
  testColumn.at(3) = 0xE5;
  testBlock.push_back(testColumn);
  testBlocks.push_back(testBlock);
  printBlocks(testBlocks);
  cout << endl << "mixColumns.." << endl;
  for (size_t i = 0; i < testBlocks.size(); ++i) {
    aes::mixColumns(testBlocks.at(i));
  }
  printBlocks(testBlocks);

  return 0;
}
