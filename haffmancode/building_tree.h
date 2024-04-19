#include <string>
#include <queue>
#include <unordered_map>
#include <iostream>
#include <fstream>

using namespace std;

struct Node
{
	char symbol;
	double frequency;

	Node* left;
	Node* right;

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

void build_huffman_tree(string text);
void build_huffman_tree(string text, string filename);
