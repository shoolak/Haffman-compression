#include "building_tree.h"
#include "info_character.h"
#include <iostream>
#include <fstream>
using namespace std;

#define b_to_kb 1024

int main()
{
	//TODO fix decoding
	int choose;
	cout << "Hi! Choose whatever you want" << endl;
	cout << "1. Compresion from console" << endl;
	cout << "2. Compresion from file" << endl;
	cout << "3. Decompression file" << endl;
	cout << "Your choice: " << endl;
	cin >> choose;
	if (choose == 1)
	{
		cout << "Input text: ";
		string text;
		cin >> text;
		
		data_maps maps = build_huffman_tree(text);
		for (auto pair : maps.char_prob)
			cout << pair.first << " " << pair.second << endl;
		cout << maps.ascii_char;
		
		/*for (auto pair : maps.char_prob)
			cout << pair.first << " " << pair.second << endl;
		cout << maps.haffcode_all << endl;
		Node* nd;
		nd = recreate_haffman_tree(maps.char_prob);

		string st;
		st = decodeHuffmanText(nd, maps.haffcode_all);
		cout << st;*/
	}
	else if (choose == 2)
	{
		string input;
		cout << "Enter file path: ";
		cin >> input;

		const char* file_path = input.c_str();

		cout << "Size of input file is " << get_file_size(file_path) / b_to_kb << " KB" << endl;

		data_maps maps = build_huffman_tree(file_to_string(file_path));

		size_t dot_pos = input.find_first_of('.');
		while (dot_pos != std::string::npos)
			{
				input.erase(dot_pos);
				dot_pos = input.find_last_of('.');
			}
		
		string incoded_file = input + ".cmph";
		ofstream compessed_file(incoded_file);
		const char* file_path_coded = incoded_file.c_str();
		for (auto pair : maps.char_prob)
			compessed_file << pair.first << " " << pair.second << endl;
		compessed_file << maps.ascii_char;
		cout << "Size of encoded file is " << get_file_size(file_path_coded)  << " KB" << endl;
	}
	else if (choose == 3)
	{
		data_maps maps;
		maps = parsing_file("D:\\HC_test\\test_large.cmph");
		for (auto pair : maps.char_prob)
			cout << pair.first << " " << pair.second << endl;
		cout << maps.ascii_char;
	}

	return 0;
}