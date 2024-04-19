#include "building_tree.h"
#include "info_character.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
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
		build_huffman_tree(text);
	}
	else if (choose == 2)
	{
		string file_path;
		cout << "Enter file path: ";
		cin >> file_path;
		//string file = "D:\\testing.txt";
		build_huffman_tree(file_to_string(file_path), file_path);
	}

	return 0;
}