#include "building_tree.h"
#include "info_character.h"


Node* new_node(char symbol, double frequency, Node* left, Node* right)
{
	Node* node = new Node();

	node->symbol = symbol;
	node->frequency = frequency;
	node->left = left;
	node->right = right;

	return node;
}

void encode(Node* root, string str, unordered_map<char, string>& huffmanCode)
{
	if (root == nullptr)
		return;

	if (!root->left && !root->right) {
		huffmanCode[root->symbol] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, int& index, string str)
{
	if (root == nullptr) {
		return;
	}

	// found a leaf node
	if (!root->left && !root->right)
	{
		cout << root->symbol;
		return;
	}

	index++;

	if (str[index] == '0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

void buildHuffmanTree(string text)
{
	unordered_map<char, double> map;
	calc_freq(text, map);

	priority_queue<Node*, vector<Node*>, compare_node> pq;

	for (auto pair : map) {
		pq.push(new_node(pair.first, pair.second, nullptr, nullptr));
	}

	while (pq.size() != 1)
	{
		Node* left = pq.top();
		pq.pop();
		Node* right = pq.top();
		pq.pop();

		//create new leaf from sum of two min frequency
		int sum = left->frequency + right->frequency;
		pq.push(new_node('\0', sum, left, right));
	}

	// pointer to root of the tree
	Node* root = pq.top();


	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "Probability of symbols: " << "\n";
	for (auto pair : map)
	{
		cout << pair.first << " " << pair.second << '\n';
	}
	cout << "\n";

	cout << "Huffman Codes are :\n";
	for (auto pair : huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}

	

	cout << "\nOriginal string was :\n" << text << '\n';


	string str = "";
	for (char ch : text) {
		str += huffmanCode[ch];
	}

	cout << "\nEncoded string is :\n" << str << '\n';

	int index = -1;
	cout << "\nDecoded string is: \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}
	cout << endl;
}