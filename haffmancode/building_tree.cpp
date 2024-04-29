#include "building_tree.h"
#include "info_character.h"
#include <sstream> 

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

char binaryToChar(string code)//converting 8 digits to the ascii symbol
{
	int decimal = stoi(code, nullptr, 2); 
	return static_cast<char>(decimal);
	
}

data_maps build_huffman_tree(string text)
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
	return maps;
}

Node* recreate_haffman_tree(unordered_map<char, double>& char_prob) {
	priority_queue<Node*, vector<Node*>, compare_node> pq;

	for (auto pair : char_prob) {
		pq.push(new Node{ pair.first, pair.second, nullptr, nullptr });
	}

	while (pq.size() != 1)
	{
		Node* left = pq.top();
		pq.pop();
		Node* right = pq.top();
		pq.pop();

		double sum = left->frequency + right->frequency;
		pq.push(new Node{ '\0', sum, left, right });
	}

	return pq.top();
}

string decode_huffman_text(Node* root, string& encodedText) {
	string decodedText = "";
	Node* curr = root;
	for (char bit : encodedText) {
		if (bit == '0') {
			curr = curr->left;
		}
		else {
			curr = curr->right;
		}
		if (curr->left == nullptr && curr->right == nullptr) {
			decodedText += curr->symbol;
			curr = root;
		}
	}
	return decodedText;
}

data_maps parsing_file(string text)
{
	data_maps data;
	ifstream file(text);

	char ch;
	double prob;
	streampos currentPosition;
	std::string line;
	while (getline(file, line))
	{
		std::stringstream ss{ line };
		if (ss >> ch >> prob) {
			data.char_prob[ch] = prob;
		}
		else {
			data.ascii_char += line;
		}
	}
	return data;
}

unsigned long long int get_file_size(const char* file_name) // return size of file. _ftelli64 return a current position in a file(apllies to only Visual Studio).Normal form is ftello64
{ 
	FILE* file = fopen(file_name, "rb");
	fseek(file, 0, SEEK_END);
	unsigned long long int size = _ftelli64(file);
	fclose(file);
	return size;
} 
string stringToBinary(const std::string& str) {
	std::string binaryString;
	for (char c : str) {
		// Convert character to ASCII value
		int asciiValue = static_cast<int>(c);

		// Convert ASCII value to binary
		std::bitset<8> binary(asciiValue);

		// Append binary representation of the character to the result string
		binaryString += binary.to_string();
	}
	return binaryString;
}


