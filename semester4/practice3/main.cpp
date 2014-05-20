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

string toString(const vector<aes::block> blocks) {
  std::stringstream ss;

  for (size_t i = 0; i < blocks.size(); ++i) {
    // For each block
    for (size_t j = 0; j < blocks.at(i).size(); ++j) {
      // For each row
      for (size_t k = 0; k < blocks.at(i).at(j).size(); ++k) {
        // For each value
        int value = blocks.at(i).at(j).at(k);
        if (value > 0) {
          ss << (char) value;
        }
      }
    }
  }

  return ss.str();
}

int main() {
  string selectionStr = "";
  int selection = 0;

  cout << "Please select:" << endl;
  cout << "  1) Encrypt" << endl;
  // cout << "  2) Decrypt" << endl;
  cout << "  3) Mock and debug" << endl;

  getline(cin, selectionStr);
  selection = atoi(selectionStr.c_str());

  switch (selection) {
    case 1:
    case 2: {
      string message = "";
      string keyString = "";

      // Prompt
      cout << "Message: ";
      getline(cin, message);

      cout << "Key: ";
      getline(cin, keyString);

      // Convert to blocks
      aes::block key = getKey(keyString);
      fillBlock(key); // Fill with zeros

      vector<aes::block> clearText = getBlocks(message);

      // cout << "Key:" << endl;
      // printBlock(key);
      // cout << endl;
      //
      // cout << "Message:" << endl;
      // printBlocks(clearText);

      if (selection == 1) {
        // Encrypt
        cout << "encrypting.." << endl;
        vector<aes::block> cipher = aes::encrypt(clearText, key);
        printBlocks(cipher);

        cout << "decrypting.." << endl;
        vector<aes::block> decrypted = aes::decrypt(cipher, key);
        printBlocks(decrypted);


        cout << "Message (cleartext): " << toString(decrypted) << endl;
      } else {
        // Decrypt
        cout << "decrypting.." << endl;
        vector<aes::block> decrypted = aes::decrypt(clearText, key);
        printBlocks(decrypted);
      }

      break;
    }
    case 3: {
      // Mock key
      aes::block mockKey;
      aes::column c;
      c.push_back(0x2b);
      c.push_back(0x28);
      c.push_back(0xab);
      c.push_back(0x09);
      mockKey.push_back(c);
      c.at(0) = 0x7e;
      c.at(1) = 0xae;
      c.at(2) = 0xf7;
      c.at(3) = 0xcf;
      mockKey.push_back(c);
      c.at(0) = 0x15;
      c.at(1) = 0xd2;
      c.at(2) = 0x15;
      c.at(3) = 0x4f;
      mockKey.push_back(c);
      c.at(0) = 0x16;
      c.at(1) = 0xa6;
      c.at(2) = 0x88;
      c.at(3) = 0x3c;
      mockKey.push_back(c);
      fillBlock(mockKey); // Fill with zeros

      // Mock input
      vector<aes::block> mockInput;
      aes::block mockBlock;
      aes::row r;
      r.push_back(0x32);
      r.push_back(0x88);
      r.push_back(0x31);
      r.push_back(0xe0);
      mockBlock.push_back(r);
      r.at(0) = 0x43;
      r.at(1) = 0x5a;
      r.at(2) = 0x31;
      r.at(3) = 0x37;
      mockBlock.push_back(r);
      r.at(0) = 0xf6;
      r.at(1) = 0x30;
      r.at(2) = 0x98;
      r.at(3) = 0x07;
      mockBlock.push_back(r);
      r.at(0) = 0xa8;
      r.at(1) = 0x8d;
      r.at(2) = 0xa2;
      r.at(3) = 0x34;
      mockBlock.push_back(r);
      mockInput.push_back(mockBlock);

      cout << "Mock key:" << endl;
      printBlock(mockKey);
      cout << endl;

      cout << "Mock input:" << endl;
      printBlocks(mockInput);

      cout << "Cipher:" << endl;
      vector<aes::block> cipher = aes::encrypt(mockInput, mockKey);
      printBlocks(cipher);

      cout << "Message:" << endl;
      vector<aes::block> message = aes::decrypt(cipher, mockKey);
      printBlocks(message);

      break;
    }
    default:
      cout << "This option is not available, sorry";
      break;
  }

  /*

  cout << endl << "Input:" << endl;
  printBlocks(mockInput);
  */

//  cout << endl << "getBlocks.." << endl << endl;
//  vector<aes::block> blocks = getBlocks(message);
//  printBlocks(blocks);

//  cout << endl << "subBytes.." << endl << endl;
//  for (size_t i = 0; i < mockInput.size(); ++i) {
//    aes::subBytes(mockInput.at(i));
//  }
//  printBlocks(mockInput);

//  cout << endl << "inverseSubBytes.." << endl << endl;
//  for (size_t i = 0; i < mockInput.size(); ++i) {
//    aes::inverseSubBytes(mockInput.at(i));
//  }
//  printBlocks(mockInput);

//  cout << endl << "shiftRows.." << endl << endl;
//  for (size_t i = 0; i < mockInput.size(); ++i) {
//    aes::shiftRows(mockInput.at(i));
//  }
//  printBlocks(mockInput);

//  cout << endl << "inverseShiftRows.." << endl << endl;
//  for (size_t i = 0; i < mockInput.size(); ++i) {
//    aes::inverseShiftRows(mockInput.at(i));
//  }
//  printBlocks(mockInput);

//  cout << endl << "transformate.." << endl << endl;
//  vector<aes::block> columned;
//  for (size_t i = 0; i < mockInput.size(); ++i) {
//    columned.push_back(aes::transformate(mockInput.at(i)));
//  }
//  printBlocks(columned);

//  cout << endl << "transformate#2.." << endl << endl;
//  vector<aes::block> rowed;
//  for (size_t i = 0; i < columned.size(); ++i) {
//    rowed.push_back(aes::transformate(columned.at(i)));
//  }
//  printBlocks(rowed);

//  cout << endl << "mixColumns.." << endl << endl;
//  for (size_t i = 0; i < mockInput.size(); ++i) {
//    aes::mixColumns(mockInput.at(i));
//  }
//  printBlocks(mockInput);

//  cout << endl << "inverseMixColumns.." << endl << endl;
//  for (size_t i = 0; i < mockInput.size(); ++i) {
//    aes::inverseMixColumns(mockInput.at(i));
//  }
//  printBlocks(mockInput);

// cout << endl << "getRoundKeys.." << endl << endl;
// vector<aes::block> keys = aes::getRoundKeys(key);
// printBlocks(keys);


  return 0;
}
