#include <vector>
#include <iostream>

#include "aes.h"

using namespace std;

namespace aes {
    const static unsigned char sbox[256] = {
        0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
        0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
        0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
        0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
        0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
        0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
        0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
        0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
        0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
        0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
        0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
        0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
        0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
        0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
        0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
        0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
    };

    const static char matrix[16] = {
        0x2, 0x3, 0x1, 0x1,
        0x1, 0x2, 0x3, 0x1,
        0x1, 0x1, 0x2, 0x3,
        0x3, 0x1, 0x1, 0x2
    };

    const static char inverseMatrix[16] = {
        0xe, 0xb, 0xd, 0x9,
        0x9, 0xe, 0xb, 0xd,
        0xd, 0x9, 0xe, 0xb,
        0xb, 0xd, 0x9, 0xe
    };

    const static char rconMatrix[40] = {
        0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    /**
     * Returns the given column in the rconMatrix[]
     * @param  col The index of the column to return
     * @return     The column
     */
    column rcon(int col) {
        column result;

        for (size_t i = 0; i < 16; ++i) {
            result.push_back(rconMatrix[i * 10 + col]);
        }

        return result;
    }

    /**
     * Replaces the given value with the one at the index of the int value in
     * sbox[]
     * @param v A reference to the char to replace
     */
    void subBytes(int &v) {
        v = sbox[(int) v];
    }

    /**
     * Calls subBytes() for every value in a column
     * @param c The column to substitute
     */
    void subBytes(column &c) {
        for (size_t i = 0; i < c.size(); ++i) {
            subBytes(c.at(i));
        }
    }

    /**
     * Calls subBytes() for every row in the given block
     * @param b The block to substitute
     */
    void subBytes(block &b) {
        for (size_t i = 0; i < b.size(); ++i) {
            subBytes(b.at(i));
        }
    }

    /**
     * Searches for the value in sbox[] and returns it's index
     * @param v The value to search for
     */
    void inverseSubBytes(int &v) {
        for (size_t i = 0; i < sizeof(sbox); ++i) {
            if (sbox[i] == v) {
                v = i;
                break;
            }
        }
    }

    /**
     * Calls inverseSubBytes() for each row in the given row
     * @param c The row to inverse substitute
     */
    void inverseSubBytes(column &c) {
        for (size_t i = 0; i < c.size(); ++i) {
            inverseSubBytes(c.at(i));
        }
    }

    /**
     * Calls inverseSubBytes() for every row in the given block
     * @param b The block to inverse substitute
     */
    void inverseSubBytes(block &b) {
        for (size_t i = 0; i < b.size(); ++i) {
            inverseSubBytes(b.at(i));
        }
    }

    /**
     * Applies shift-rows-step to the given row
     * @param b The row to rowtate (hah)
     */
    void shiftRows(block &b) {
        for (size_t i = 0; i < b.size(); ++i) {
            switch (i) {
                case 0:
                    break;
                case 1:
                    rotate(b.at(i).begin(), b.at(i).begin() + 1, b.at(i).end());
                    break;
                case 2:
                    rotate(b.at(i).begin(), b.at(i).begin() + 2, b.at(i).end());
                    break;
                case 3:
                    rotate(b.at(i).begin(), b.at(i).begin() + 3, b.at(i).end());
                    break;
                default:
                    break;
            }
        }
    }

    /**
     * Transformates the block. Basically just returns the columns
     * @param  b The block to transformate
     * @return   The transformated block
     *
     * Example:
     *
     *   0  1  2  3           0  4  8  c
     *   4  5  6  7  becomes  1  5  9  d
     *   8  9  a  b           2  6  a  e
     *   c  d  e  f           3  7  b  f
     *
     */
    block transformate(const block b) {
        block transformated;

        for (size_t i = 0; i < b.size(); ++i) { // Each row
            for (size_t j = 0; j < b.at(i).size(); ++j) { // Each item
                if (transformated.size() <= j) {
                    // We need more columns/rows, create one
                    vector<int> c;
                    // Push back value
                    c.push_back(b.at(i).at(j));
                    // Push back column
                    transformated.push_back(c);
                } else {
                    // Column exists, push back value
                    transformated.at(j).push_back(b.at(i).at(j));
                }
            }
        }

        return transformated;
    }

    /**
     * Performs a galois calculation
     * @param  v The value
     * @param  n The factor
     * @return   The result of the calculation
     */
    int galois(int v, int n) {
        // Get least significant bit
        // ffs() returns the index, starting at 1
        bool h = ffs(v) == 1;

        switch (n) {
            case 2: {
                v <<= 1; // Shift to the left == * 2

                if (h) {
                    v ^= 0x1B;
                }

                break;
            }
            case 3:
                v ^= galois(v, 2);
                break;
            case 9:
                v ^= galois(galois(galois(v, 2), 2), 2);
                break;
            case 11:
                v ^= galois(galois(galois(v, 2), 2) ^ v, 2);
                break;
            case 13:
                v ^= galois(galois(galois(v, 2) ^ v, 2), 2);
                break;
            case 14:
                v = galois(galois(galois(v, 2) ^ v, 2) ^ v, 2);
                break;
            default:
                break;
        }

        return v;
    }

    /**
     * Performs the mix columns step on the given block
     * @param b A reference to the block
     */
    void mixColumns(block &b) {
        block columns = transformate(b);

        int v;
        column c;
        for (size_t i = 0; i < columns.size(); ++i) { // For each column
            c = columns.at(i);
            for (size_t j = 0; j < c.size(); ++j) { // For each value
                v = 0;

                // Loop through each value, xor with galois product with matrix[]
                for (size_t k = 0; k < columns.at(i).size(); ++k) {
                    v ^= galois(c.at(k), matrix[j * 4 + k]);
                }

                columns.at(i).at(j) = v % 256;
            }
        }

        b = transformate(columns);
    }

    /**
     * Like mixColumns() but the other way
     * @param b The block to invert mix-columns
     */
    void inverseMixColumns(block &b) {
        block columns = transformate(b);

        int newContentTmp;
        int newContent;
        column c;
        for (size_t i = 0; i < columns.size(); ++i) { // For each column
            c = columns.at(i);
            for (size_t j = 0; j < c.size(); ++j) { // For each value
                newContentTmp = 0;
                newContent = 0;
                // Loop through each value, xor with galois product with matrix[]
                for (size_t k = 0; k < c.size(); ++k) {
                    newContent ^= galois(c.at(k), inverseMatrix[j * 4 + k]);
                }
                columns.at(i).at(j) = newContent % 256;
                newContent = 0;
            }
        }

        b = transformate(columns);
    }

    /**
     * Returns a vector with the ten (10) round keys
     * @param  key The key to expand
     * @return     The round keys
     */
    vector<block> getRoundKeys(const block key) {
        vector<block> roundKeys;
        roundKeys.push_back(key);

        block lastBlockColumns;
        column lastColumn;
        for (size_t i = 0; i < 10; ++i) {
            // Get last column
            lastBlockColumns = transformate(roundKeys.at(i));
            lastColumn = lastBlockColumns.at(3);

            // Rotate to the left
            rotate(lastColumn.begin(), lastColumn.begin() + 1, lastColumn.end());

            // Substitute
            subBytes(lastColumn);

            // Xor with first column and rcon
            column nextColumn;
            column firstColumn = lastBlockColumns.at(0);
            column tmpRcon = rcon(i);

            for (size_t i = 0; i < 4; ++i) {
                int rcon = tmpRcon.at(i);
                if (rcon == -128) rcon = 128; // Kill me

                nextColumn.push_back(firstColumn.at(i) ^ lastColumn.at(i) ^ rcon);
            }

            // Create next block and push next column
            block nextBlock;
            nextBlock.push_back(nextColumn);

            for (size_t i = 1; i < 4; ++i) {
                column newColumn;

                for (size_t j = 0; j < 4; ++j) {
                    newColumn.push_back(nextBlock.at(i - 1).at(j) ^ lastBlockColumns.at(i).at(j));
                }

                nextBlock.push_back(newColumn);
            }

            roundKeys.push_back(transformate(nextBlock));
        }

        return roundKeys;
    }

    /**
     * XOR a block with a key
     * @param b A reference to a block
     * @param k The key
     */
    void addRoundKey(block &b, block k) {
        for (size_t i = 0; i < b.size(); ++i) {
            for (size_t j = 0; j < b.at(i).size(); ++j) {
                b.at(i).at(j) ^= k.at(i).at(j);
            }
        }
    }

    /**
     * Performs a round
     * @param b A reference to a block
     * @param k The key
     */
    void roundIt(block &b, const block k) {
        subBytes(b);
        shiftRows(b);
        mixColumns(b);
        addRoundKey(b, k);
    }

    /**
     *  Encrypt function
     *  @param  input A vector with 128-bit blocks containing the message
     *  @param  key   The key
     *  @return       The cipher
     */
    vector<block> encrypt(const vector<block> input, const block key) {
        vector<block> roundKeys = getRoundKeys(key);
        vector<block> cipher = input;

        // Initial round
        for (size_t i = 0; i < cipher.size(); ++i) {
            addRoundKey(cipher.at(i), roundKeys.at(0));
        }

        for (size_t i = 0; i < 9; ++i) {
            for (size_t j = 0; j < cipher.size(); ++j) {
                roundIt(cipher.at(j), roundKeys.at(i + 1));
            }
        }

        // Final round
        for (size_t i = 0; i < cipher.size(); ++i) {
            subBytes(cipher.at(i));
            shiftRows(cipher.at(i));
            addRoundKey(cipher.at(i), roundKeys.at(10));
        }

        return cipher;
    }

    /**
     * Like roundIt(), but reverse (you don't say)
     * @param input    The block to apply the round on
     * @param roundKey The roundKey
     */
    void inverseRoundIt(block &input, const block roundKey) {
        addRoundKey(input, roundKey);
        inverseMixColumns(input);
        inverseShiftRows(input);
        inverseSubBytes(input);
    }

    /**
     * Like shiftRows(), but reverse
     * @param b A reference to the block to apply the shift-rows step on
     */
    void inverseShiftRows(block &b) {
        for (size_t i = 0; i < b.size(); ++i) {
            switch (i) {
                case 0:
                    break;
                case 1:
                    rotate(b.at(i).begin(), b.at(i).end() - 1, b.at(i).end());
                    break;
                case 2:
                    rotate(b.at(i).begin(), b.at(i).end() - 2, b.at(i).end());
                    break;
                case 3:
                    rotate(b.at(i).begin(), b.at(i).end() - 3, b.at(i).end());
                    break;
                default:
                    break;
            }
        }
    }

    /**
     * Decrypt function
     * @param  cipher A vector with blocks containing the cipher
     * @param  key    The key
     * @return        A vector with blocks containing the message
     */
    vector<block> decrypt(const vector<block> cipher, const block key) {
        vector<block> roundKeys = getRoundKeys(key);
        vector<block> clearText = cipher;

        // Final Round
        for (size_t i = 0; i < clearText.size(); ++i) {
            addRoundKey(clearText.at(i), roundKeys.at(10));
            inverseShiftRows(clearText.at(i));
            inverseSubBytes(clearText.at(i));
        }

        // All Rounds
        for (size_t i = 9; i > 0; --i) {
            // Key loop
            for (size_t j = 0; j < clearText.size(); ++j) {
                // Block loop
                inverseRoundIt(clearText.at(j), roundKeys.at(i));
            }
        }

        // Initial Round
        for (size_t i = 0; i < clearText.size(); ++i) {
            addRoundKey(clearText.at(i), roundKeys.at(0));
        }

        return clearText;
    }
}
