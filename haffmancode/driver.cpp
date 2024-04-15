#include "building_tree.h"
#include "info_character.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	//TODO avoid ipch folder for github
	
	string file = "example.txt";
	build_huffman_tree(file_to_string(file));

	return 0;
}