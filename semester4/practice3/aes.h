#include <vector>

using namespace std;

namespace aes {
  typedef std::vector<int> row;
  typedef std::vector<int> column;
  typedef std::vector<row> block;

  void subBytes(block &b);
  void shiftRows(block &b);
  block transformate(const block b);
  void mixColumns(block &b);
  vector<block> getRoundKeys(const block key);
  vector<block> encrypt(const vector<block> input, const block key);
  vector<block> decrypt(const vector<block> cipher, const block key);
}
