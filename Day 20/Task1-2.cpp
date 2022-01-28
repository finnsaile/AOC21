#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>

using namespace std;

void add_padding(list<list<char>>& _map, const char& c)
{
    for(auto iter = _map.begin(); iter != _map.end(); iter++)
    {
        iter->push_front(c);
        iter->push_back(c);
    }

    _map.push_front(list<char>(_map.back().size(), c));
    _map.push_back(list<char>(_map.back().size(), c));
}

int32_t calculate_new_char_index(const int32_t& y, const int32_t& x, const vector<vector<char>>& temp_vec, const char& current_padding)
{   
    string bin_string;
    for(int32_t i = -1; i <= 1; i++)
    {
        for(int32_t j = -1; j <= 1; j++)
        {
            if(y + i < 0 || x + j < 0 || y + i >= temp_vec.size() || x + j >= temp_vec.back().size())
                bin_string.push_back(current_padding);
            else
                bin_string.push_back(temp_vec[y + i][x + j]);
        }
    }
    return stoi(bin_string, nullptr, 2);
}

void apply_algorithm(list<list<char>>& _map, const string& image_enhance_algorithm, const char& current_padding)
{
    char temp;
    vector<vector<char>> temp_vec;
    int32_t i, j;
    add_padding(_map, current_padding);
    for(auto m_iter = _map.begin(); m_iter != _map.end(); m_iter++)
    {
        temp_vec.push_back(vector<char>());
        for(auto r_iter = m_iter->begin(); r_iter != m_iter->end(); r_iter++)
        {
            temp_vec.back().push_back(*r_iter);
        }
    }

    i = 0;
    for(auto m_iter = _map.begin(); m_iter != _map.end(); m_iter++)
    {
        j = 0;
        for(auto r_iter = m_iter->begin(); r_iter != m_iter->end(); r_iter++)
        {   
            temp = image_enhance_algorithm[calculate_new_char_index(i, j, temp_vec, current_padding)];
            if(temp == '#')
                *r_iter = '1';
            else
                *r_iter = '0';
            j++;
        }
        i++;
    }
}

int main()
{
    const int32_t enhance_amount = 2;
    ifstream file("log.txt");
    string in, image_enhance_algorithm;
    list<list<char>> map;

    getline(file, image_enhance_algorithm);
    getline(file, in);
    
    while(getline(file, in))
    {
        map.push_back(list<char>());
        for(char& c: in)
        {
            if(c == '#')
                map.back().push_back('1');
            else
                map.back().push_back('0');
        }
    }

    for(int32_t i = 0; i < enhance_amount; i++)
    {
        if(i % 2 == 0)
            apply_algorithm(map, image_enhance_algorithm, '0');
        else
            apply_algorithm(map, image_enhance_algorithm, '1');
    }

    int32_t counter = 0;
    for(auto& m: map)
    {
        for(auto& c: m)
        {
            if(c == '1')
                counter++;
        }
    }
    cout << counter << endl;
}