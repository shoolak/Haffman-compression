#include "building_tree.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	string file_path = "D:\\testing.txt";
	string temp;
	string text_file;
	ifstream file(file_path);
	if (file.is_open()) {
		while (getline(file, temp))
		{
			text_file += temp + "\n";
		}
	}
	
	cout << text_file;
	/*cout << "Input: ";
	string text;
	cin >> text;*/

	build_huffman_tree(text_file);

	return 0;
}