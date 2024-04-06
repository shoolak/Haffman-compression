#include <iostream>

#include <unordered_map>
#include <string>

#include "info_character.h"

using namespace std;

int main()
{
    string text;
    cout << "plz write some stuff" << endl;
    cin >> text;

    unordered_map<char, double> symb_freq;
    calc_freq(text, symb_freq);
    for (const auto& pair : symb_freq) {
        cout << pair.first <<":"<< pair.second << endl;
    }
    return 0;

}