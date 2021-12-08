#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Display
{
    public:
        Display(string &in);
        void print_strings();
        int32_t get_sum_of_t1();
        int32_t get_sum_of_t2();
    private:
        int32_t find_pos(int32_t size); 
        bool contains(string& search_string, int32_t value, int32_t places);
        vector<string> m_signal_patterns;
        vector<string> m_output_values;
};

Display::Display(string &in)
{
    int32_t delimiter_pos;

    for(int32_t i = 0; i < 10; i++)
    {
        delimiter_pos = in.find(' ');
        m_signal_patterns.push_back(in.substr(0, delimiter_pos));
        in.erase(0, delimiter_pos + 1);
    }

    in.erase(0, 2);

    for(int32_t i = 0; i < 4; i++)
    {
        delimiter_pos = in.find(' ');
        m_output_values.push_back(in.substr(0, delimiter_pos));
        in.erase(0, delimiter_pos + 1);
    }
}

void Display::print_strings()
{
    for(string& value: m_signal_patterns)
        cout << value << " ";

    for(string& value: m_output_values)
        cout << value << " ";

    cout << endl;
}

int32_t Display::get_sum_of_t1()
{
    int32_t sum = 0;
    for(string& value: m_output_values)
        if(value.length() == 2 || value.length() == 3 || value.length() == 4 || value.length() == 7)
            sum++;
    return sum;
}

int32_t Display::find_pos(int32_t size)
{
    for(int32_t i = 0; i < m_signal_patterns.size(); i++)
        if(m_signal_patterns[i].size() == size)
            return i;

    return -1;
}

bool Display::contains(string& search_string, int32_t value, int32_t places)
{
    if(value == 7)
        value = 3;

    int32_t contains_total = 0;
        for(char& ch: m_signal_patterns[find_pos(value)])
        {
            for(char& ch_pat: search_string)
                if(ch_pat == ch)
                    contains_total++;
        }
    
    if(contains_total == places)
        return true;
    else
        return false;
}

int32_t Display::get_sum_of_t2()
{
    string num_string;
    for(string& value: m_output_values)
    {
        switch (value.length())
        {
        case 2: num_string.push_back('1'); break;
        case 3: num_string.push_back('7'); break;
        case 4: num_string.push_back('4'); break;
        case 7: num_string.push_back('8'); break;

        case 5: if(contains(value, 7, 3)) 
                    num_string.push_back('3'); 
                else if(contains(value, 4, 3))
                    num_string.push_back('5');
                else
                    num_string.push_back('2');
                break;
        case 6: if(contains(value, 4, 4)) 
                    num_string.push_back('9'); 
                else if(contains(value, 7, 3))
                    num_string.push_back('0');
                else
                    num_string.push_back('6');
                break;
        default:
            break;
        }
    }
    return stoi(num_string);
}

int main()
{
    ifstream input("log.txt");
    string in;
    int32_t sum = 0, sum2 = 0;
    vector<Display> display_vec;

    while(getline(input, in))
    {
        display_vec.push_back(Display(in));
        sum += display_vec.back().get_sum_of_t1();
        sum2 += display_vec.back().get_sum_of_t2();
    }
    cout << "Task1: " << sum << endl;
    cout << "Task2: " << sum2 << endl;
    input.close();
}