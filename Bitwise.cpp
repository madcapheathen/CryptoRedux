// Bitwise.cpp

#include "Bitwise.h"

vector< bitset<8> > hex_to_bits(string hex){
	vector< bitset<8> > bits;
	for (int i = 0; i < hex.size(); i += 2){
		int next = 0;
		for (int j = 0; j < 2; ++j){
			if (hex.at(i + j) <= '9'&&hex.at(i + j) >= '0'){
				next += int((hex.at(i + j) - '0'))*(1 + 15 * (1 - j));
			}
			else if (hex.at(i + j) <= 'f'&&hex.at(i + j) >= 'a'){
				next += int((hex.at(i + j) - 'a') + 10)*(1 + 15 * (1 - j));
			}
			else{
				next += int((hex.at(i + j) - 'A') + 10)*(1 + 15 * (1 - j));
			}
		}
		bits.push_back(bitset<8>(next));
	}
	return bits;
}

string bits_to_b64(vector<bitset<8>> bits){
	string charlist = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	string b64;
	int blocks = bits.size() / 3;
	int offset = bits.size() % 3;
	for (int i = 0; i < blocks; ++i){
		for (int j = 0; j < 4; ++j){
			bitset<6> next;
			for (int k = 0; k < 6; ++k){
				next[5 - k] = bits.at(3 * i + ((6 * j + k) / 8))[7 - ((6 * j + k) % 8)]; // operator[] goes backwards with bitsets, so I had to resort to goddamn sorcery here
			}
			b64.push_back(charlist.at(next.to_ulong()));
		}
	}
	if (offset > 0){
		for (int j = 0; j < (4 - (3 - offset)); ++j){
			bitset<6> next;
			for (int k = 0; k < 6; ++k){
				if (3 * blocks + (6 * j + k) / 8 < bits.size()){
					next[5 - k] = bits.at(3 * blocks + ((6 * j + k) / 8))[7 - ((6 * j + k) % 8)];
				}
				else{
					next[5 - k] = false;
				}
			}
			b64.push_back(charlist.at(next.to_ulong()));
		}
		for (int i = 0; i < 3 - offset; ++i){
			b64.push_back('=');
		}
	}
	return b64;
}

string bits_to_hex(vector< bitset<8> > bits){
	string charlist = "0123456789abcdef";
	string hex;
	for (int i = 0; i < bits.size(); ++i){
		hex.push_back(charlist.at(bits.at(i).to_ulong() / 16));
		hex.push_back(charlist.at(bits.at(i).to_ulong() % 16));
	}
	return hex;
}

vector< bitset<8> > xor(vector<bitset<8>> first, vector<bitset<8>> second){
	vector< bitset<8> > result(first);
	for (int i = 0; i < result.size(); ++i){
		result.at(i) = first.at(i) ^ second.at(i);
	}
	return result;
}