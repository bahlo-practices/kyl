#include <vector>

using namespace std;

namespace aes {
  typedef std::vector<int> row;
  typedef std::vector<int> column;
  typedef std::vector<row> block;

  void subBytes(block &b);
  void shiftRows(block &b);
  vector<column> getColumns(const block b);
  void mixColumns(block &b);
}
