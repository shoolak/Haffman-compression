#include <string>
#include <queue>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <stdio.h>



using namespace std;

struct Node
{
	char symbol;
	double frequency;

	Node* left;
	Node* right;

};

struct data_maps {
	unordered_map<char, double> char_prob; //for symbol and probabilities
	unordered_map<char, string> char_haffcode; // for symbol and haffman code
	string haffcode_all; // for code that haffman algo do, example 101011010010
	string ascii_char; // for ascii representation for binary code  01001111 = 'O'
};

struct compare_node {
	bool operator()(Node* left, Node* right)
	{
		return left->frequency > right->frequency;
	}
};


Node* new_node(char symbol, double frequency, Node* left, Node* right);

void encode(Node* root, string str, unordered_map<char, string>& huffmanCode);

void decode(Node* root, int& index, string str);

data_maps build_huffman_tree(string text);
//void build_huffman_tree(string text, string filename);

unsigned long long int get_file_size(const char* file_name);
