// Bitwise.h
//
// Converts to and from and operates on vector<bitset[8]>

#include "Standard_Include.h"

using namespace std;

vector< bitset<8> > hex_to_bits(string hex);
string bits_to_b64(vector< bitset<8> > bits);
string bits_to_hex(vector< bitset<8> > bits);
vector< bitset<8> > xor(vector<bitset<8>> first, vector<bitset<8>> second);