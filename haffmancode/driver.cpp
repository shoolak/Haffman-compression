#include "building_tree.h"
#include "info_character.h"
#include <iostream>
#include <fstream>
using namespace std;

#define b_to_kb 1024

int main()
{
	// // TODO: separete decoding
	// // TODO: headers for decoding
	int choose;
	cout << "Hi! Choose the comppresion you want from" << endl;
	cout << "1. From console" << endl;
	cout << "2. From file" << endl;
	cout << "Your choice: " << endl;
	cin >> choose;
	if (choose == 1)
	{
		cout << "Input text: ";
		string text;
		cin >> text;
		
		data_maps maps = build_huffman_tree(text);

		cout << maps.haffcode_all << endl;
		cout << maps.ascii_char << endl;
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
		compessed_file << maps.ascii_char;
		cout << "Size of encoded file is " << get_file_size(file_path_coded)  << " KB" << endl;
	}

	return 0;
}