#pragma once

using namespace std;

#include <fstream>
#include <string>
#include <unordered_map>

void calc_freq(std::string text,std::unordered_map<char, double> &map );
string file_to_string(string filename);