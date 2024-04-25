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
		huffmanCode[(unsigned char )root->symbol] = str;
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

char binaryToChar(string code)//converting 8 digits to the ascii symbol
{
	int decimal = stoi(code, nullptr, 2); 
	return static_cast<char>(decimal);
	
}

data_maps build_huffman_tree(string text) //for console
{
	data_maps maps;
	calc_freq(text, maps.char_prob);

	priority_queue<Node*, vector<Node*>, compare_node> pq;

	for (auto pair : maps.char_prob) {
		pq.push(new_node(pair.first, pair.second, nullptr, nullptr));
	}

	while (pq.size() != 1)
	{
		Node* left = pq.top();
		pq.pop();
		Node* right = pq.top();
		pq.pop();

		double sum = left->frequency + right->frequency;//create new leaf from sum of two min frequency
		pq.push(new_node('\0', sum, left, right));
	}

	
	Node* root = pq.top(); // pointer to root of the tree

	encode(root, "", maps.char_haffcode);
	for (char ch : text) {
		maps.haffcode_all += maps.char_haffcode[ch];
	}
	for (size_t i = 0, d = 0; i < maps.haffcode_all.length(); i += 8, d++)
	{
		string chunk = maps.haffcode_all.substr(i, 8);
		maps.ascii_char += binaryToChar(chunk);
	}

	
	/*int index = -1;
	while (index < (int)maps.haffcode_all.size() - 2) {
		decode(root, index, maps.haffcode_all);
	}*/
	
	
	return maps;
}

unsigned long long int get_file_size(const char* file_name) // return size of file. _ftelli64 return a current position in a file(apllies to only Visual Studio).Normal form is ftello64
{ 
	FILE* file = fopen(file_name, "rb");
	fseek(file, 0, SEEK_END);
	unsigned long long int size = _ftelli64(file);
	fclose(file);
	return size;
} 


