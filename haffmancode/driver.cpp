#include "building_tree.h"

using namespace std;

int main()
{
	cout << "Input: ";
	string text;
	cin >> text;

	buildHuffmanTree(text);

	return 0;
}