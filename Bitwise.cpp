// Bitwise.cpp

#include "Bitwise.h"

vector< bitset<8> > hex_to_bits(string hex){
	vector< bitset<8> > bits;
	for (int i = 0; i < hex.size(); i+=2){
		int next=0;
		for (int j = 0; j < 2; ++j){
			if (hex.at(i + j) <= '9'&&hex.at(i + j) >= '0'){
				next += int((hex.at(i + j) - '0'))*(1 + 15 * (1 - j));
			}
			else if (hex.at(i + j) <= 'f'&&hex.at(i + j) >= 'a'){
				next += int((hex.at(i + j) - 'a')+10)*(1 + 15 * (1 - j));
			}
			else{
				next += int((hex.at(i + j) - 'A')+10)*(1 + 15 * (1 - j));
			}
		}
		bits.push_back(bitset<8> (next));
	}
	return bits;
}

string bits_to_b64(vector<bitset<8>> bits){
	string b64;

	return b64;
}