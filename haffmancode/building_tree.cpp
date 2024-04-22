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
char binaryToChar(string code)
{
	int decimal = stoi(code, nullptr, 2); 
	return static_cast<char>(decimal);
	
}//converting 8 digits to the ascii symbol
void build_huffman_tree(string text) //for console
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
		double sum = left->frequency + right->frequency;
		pq.push(new_node('\0', sum, left, right));
	}

	// pointer to root of the tree
	Node* root = pq.top();


	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "Probability of symbols: " << "\n";
	
	for (auto pair : map)
	{
		if (pair.first != '\n')
			cout << pair.first << " " << pair.second << '\n';
		else
			cout << "next_line_symbol " << pair.second << '\n';
	}
	cout << "\n";

	cout << "Huffman Codes are :\n";
	for (auto pair : huffmanCode) {
		if (pair.first != '\n')
			cout << pair.first << " " << pair.second << '\n';
		else
			cout << "next_line_symbol " << pair.second << '\n';
	}

	

	cout << "\nOriginal string was :\n" << text << '\n';


	string str = "";
	for (char ch : text) {
		str += huffmanCode[ch];
	}
	cout << "\nEncoded string is :\n" << str << '\n';
	for (size_t i = 0; i < str.length(); i += 8)
	{
		string chunk = str.substr(i, 8);
		cout << binaryToChar(chunk);
	}
	//cout << "\nEncoded string is :\n" << str << '\n';

	int index = -1;
	cout << "\nDecoded string is: \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}
	cout << endl;
}

void build_huffman_tree(string text, string filename) // for file
{
	size_t dot_pos = filename.find_first_of('.');
	while (dot_pos != std::string::npos)
	{
		filename.erase(dot_pos);
		dot_pos = filename.find_last_of('.');
	}
	string new_file_general_info = filename + "_general_info.cmph";
	string incoded_file = filename + ".cmph";
	ofstream general_info(new_file_general_info);
	ofstream compessed_file(incoded_file);
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
		double sum = left->frequency + right->frequency;
		pq.push(new_node('\0', sum, left, right));
	}

	// pointer to root of the tree
	Node* root = pq.top();


	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	general_info << "Probability of symbols: " << "\n";

	for (auto pair : map)
	{
		if (pair.first != '\n')
			general_info << pair.first << " " << pair.second << '\n';
		else
			general_info << "next_line_symbol " << pair.second << '\n';
	}
	cout << "\n";

	general_info << "Huffman Codes are :\n";
	for (auto pair : huffmanCode) {
		if (pair.first != '\n')
			general_info << pair.first << " " << pair.second << '\n';
		else
			general_info << "next_line_symbol " << pair.second << '\n';
	}



	general_info << "\nOriginal string was :\n" << text << '\n';


	string str = "";
	for (char ch : text) {
		str += huffmanCode[ch];
	}
	for (size_t i = 0; i < str.length(); i += 8)
	{
		string chunk = str.substr(i, 8);
		compessed_file << binaryToChar(chunk);
	}
	int index = -1;
	general_info << "\nDecoded string is: \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}
	cout << endl;
}

unsigned long long int get_file_size(const char* file_name) {
	FILE* file = fopen(file_name, "rb");
	fseek(file, 0, SEEK_END);
	unsigned long long int size = _ftelli64(file);
	fclose(file);
	return size;
} // return size of file. _ftelli64 return a current position in a file(apllies only with Visual Studio).Normal form is ftello64
 // TODO Headers for decoding
 // TODO why coded file is larger that normal++
