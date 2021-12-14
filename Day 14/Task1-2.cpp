#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <limits>

#define STEPS 40
using namespace std;

struct Result
{
    Result(char c) : resulting_char{c} {}
    int64_t pair_count = 0;
    int64_t new_count = 0;
    char resulting_char;
};

int main()
{
    ifstream file("log.txt");
    string in, polymer_template;
    getline(file, polymer_template);
    unordered_map<string, Result> rule_map;
    int64_t char_counter[25], max_count = 0, min_count = __INT64_MAX__;

    for(int32_t i = 0; i < 25; i++)
        char_counter[i] = 0;

    while(getline(file, in))
    {
        if(!in.empty())
            rule_map.insert(pair<string, Result>(in.substr(0, 2), Result(in.back())));
    }

    for(int32_t i = 0; i < polymer_template.size() - 1; i++)
    {
        rule_map.find(polymer_template.substr(i, 2))->second.pair_count++;
        char_counter[polymer_template[i] - 'A']++;
    }
    char_counter[polymer_template.back() - 'A']++;

    for(int32_t i = 0; i < STEPS; i++)
    {
        for(auto& elem: rule_map)
        {   
            if(elem.second.pair_count > 0)
            {
                rule_map.find(elem.first.substr(0, 1) + elem.second.resulting_char)->second.new_count += elem.second.pair_count;
                rule_map.find(elem.second.resulting_char + elem.first.substr(1, 1))->second.new_count += elem.second.pair_count;
                char_counter[elem.second.resulting_char - 'A'] += elem.second.pair_count;
            }
        }

        for(auto& elem: rule_map)
        {
            elem.second.pair_count = elem.second.new_count;
            elem.second.new_count = 0;
        }
    }

    for(int64_t i: char_counter)
    {
        if(i > max_count)
            max_count = i;
        if(i != 0 && i < min_count)
            min_count = i;
    }
    cout << "Max: " << max_count << ", Min: " << min_count << "\nMax - Min: " << max_count << " - " << min_count << " = " << max_count - min_count << endl;
    file.close();
}