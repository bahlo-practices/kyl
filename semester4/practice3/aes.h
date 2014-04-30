#include <vector>


namespace aes {
  typedef std::vector<int> row;
  typedef std::vector<row> block;

  void subBytes(block &b);
  void shiftRows(block &b);
  void mixColumns(block &b);
}
