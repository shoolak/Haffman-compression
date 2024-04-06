#pragma once
struct Node
{
	char symbol;
	double frequency;
	Node* left;
	Node* right;

	Node(char symbol, double frequency) :symbol(symbol), frequency(frequency), left(nullptr), right(nullptr) {}
};