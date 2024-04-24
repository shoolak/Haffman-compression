#include "info_character.h"

void calc_freq(std::string text, std::unordered_map<char, double> &map)
{
    const double size = text.size();
    for (char ch : text)
    {
        map[ch]++;
    }
    for (auto& pair : map){
        pair.second = pair.second / (double)size;
    }

}

string file_to_string(string filename)
{
    ifstream file(filename);
    string text_file;
    string temp;

    if (file.is_open()) {
        while (getline(file, temp))
        {
            text_file += temp + "\n";
        }
    }
    return text_file;
}