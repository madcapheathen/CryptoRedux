// CryptoRedux.cpp : 
//
// Now with 100% more Git!

#include "Standard_Include.h"
#include "Bitwise.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	// Set 1, Challenge 1
	//cout << bits_to_b64(hex_to_bits("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d")) << endl;

	// Set 1, Challenge 2
	//vector<bitset<8>> first = hex_to_bits("1c0111001f010100061a024b53535009181c");
	//vector<bitset<8>> second = hex_to_bits("686974207468652062756c6c277320657965");
	//cout << bits_to_hex(xor(first, second)) << endl;

	// Set 1, Challenge 3
	//cout << bits_to_text(single_character_xor(hex_to_bits("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"))) << endl;

	// Set 1, Challenge 4
	//fstream fs("4.txt");
	//string best_hex = "";
	//vector<bitset<8>> best_text;
	//int high_score = 0;
	//while (!fs.eof()){
	//	string next = "";
	//	getline(fs, next);
	//	vector<bitset<8>> result = single_character_xor(hex_to_bits(next));
	//	int score = score_char_freq(result);
	//	if (score > high_score){
	//		high_score = score;
	//		best_hex = next;
	//		best_text = result;
	//	}
	//}
	//cout << "Encoded string: " << best_hex << endl;
	//cout << "Decoded to: " << bits_to_text(best_text) << endl;

	// Set 1, Challenge 5
	fstream fs("5in.txt");
	string ciphertext;
	char next = fs.get();
	while (!fs.eof()){
		ciphertext.push_back(next);
		next = fs.get();
	}
	cout << bits_to_hex(encrypt_RKXOR(text_to_bits(ciphertext), text_to_bits("ICE"))) << endl;
	return 0;
}

