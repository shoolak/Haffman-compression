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