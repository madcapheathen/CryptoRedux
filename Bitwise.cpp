// Bitwise.cpp

#include "Bitwise.h"
#include <map>

const string LOWERCASE = "abcdefghijklmnopqrstuvwxyz ";
const string UPPERCASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
const string B64CHARLIST = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const string HEXCHARLIST = "0123456789abcdef";

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
	string b64;
	int blocks = bits.size() / 3;
	int offset = bits.size() % 3;
	for (int i = 0; i < blocks; ++i){
		for (int j = 0; j < 4; ++j){
			bitset<6> next;
			for (int k = 0; k < 6; ++k){
				next[5 - k] = bits.at(3 * i + ((6 * j + k) / 8))[7 - ((6 * j + k) % 8)]; // operator[] goes backwards with bitsets, so I had to resort to goddamn sorcery here
			}
			b64.push_back(B64CHARLIST.at(next.to_ulong()));
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
			b64.push_back(B64CHARLIST.at(next.to_ulong()));
		}
		for (int i = 0; i < 3 - offset; ++i){
			b64.push_back('=');
		}
	}
	return b64;
}

string bits_to_hex(vector< bitset<8> > bits){
	string hex;
	for (int i = 0; i < bits.size(); ++i){
		hex.push_back(HEXCHARLIST.at(bits.at(i).to_ulong() / 16));
		hex.push_back(HEXCHARLIST.at(bits.at(i).to_ulong() % 16));
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

int score_char_freq(vector<bitset<8>> text){
	int weights[] = {81,15,28,43,127,22,20,61,70,2,8,40,24,67,75,19,1,60,63,91,28,10,24,2,20,1,128};
	int score=0;
	for (int i = 0; i < text.size(); ++i){
		int current = LOWERCASE.find(char(text.at(i).to_ulong()));
		if (current >= 0){
			score += weights[current];
		}
		else{
			current = UPPERCASE.find(char(text.at(i).to_ulong()));
			if (current >= 0){
				score += weights[current];
			}
		}
	}
	return score;
}

vector<bitset<8>> single_character_xor(vector<bitset<8>> cipher){
	int max_score = 0;
	vector<bitset<8>> winner;
	for (int i = 0; i < 256; ++i){
		vector<bitset<8>> next = cipher;
		bitset<8> single_char(i);
		for (int k = 0; k < next.size(); ++k){
			next.at(k) ^= single_char;
		}
		int score = score_char_freq(next);
		if (score > max_score){
			max_score = score;
			winner = next;
		}
	}
	return winner;
}

string bits_to_text(vector<bitset<8>> bits){
	string result;
	for (int i = 0; i < bits.size(); ++i){
		result.push_back(char(bits.at(i).to_ulong()));
	}
	return result;
}