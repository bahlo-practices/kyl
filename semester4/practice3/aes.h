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
  string hash(const vector<block> b, const block k);
}
