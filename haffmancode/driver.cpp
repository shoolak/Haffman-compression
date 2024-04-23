#include "building_tree.h"
#include "info_character.h"
#include <iostream>
#include <fstream>
using namespace std;

#define b_to_kb 1024

int main()
{
	
	const char* a = "D:\\HC_test\\test_large.txt";
	
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
		//string file = "D:\\testing.txt";
		//build_huffman_tree(file_to_string(file_path), file_path);
	}

	return 0;
}