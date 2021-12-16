#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <limits>

using namespace std;
unordered_map<char, string> hex_map = 
{
    {'0', "0000"},
    {'1', "0001"},
    {'2', "0010"},
    {'3', "0011"},
    {'4', "0100"},
    {'5', "0101"},
    {'6', "0110"},
    {'7', "0111"}, 
    {'8', "1000"},
    {'9', "1001"},
    {'A', "1010"},
    {'B', "1011"},
    {'C', "1100"},
    {'D', "1101"},
    {'E', "1110"},
    {'F', "1111"},
};

int64_t btoi(const string& s)
{
    return stol(s, nullptr, 2);
}

string get_package_value(string binary_string, int64_t& return_value)
{
    return_value = 0;
    vector<int64_t> return_values;
    int64_t  id = 0, length_id = 0, sub_packet_length = 0, sub_packet_amount = 0;
    string sub_packet, value_string, most_sig_bit = "1";

    id = btoi(binary_string.substr(3, 3));  
    binary_string = binary_string.substr(6);
    if(id != 4)
    {
        length_id = btoi(binary_string.substr(0, 1));
        binary_string = binary_string.substr(1);
        if(length_id == 0)
        {
            sub_packet_length = btoi(binary_string.substr(0, 15));
            binary_string = binary_string.substr(15);
            sub_packet = binary_string.substr(0, sub_packet_length);
            binary_string = binary_string.substr(sub_packet_length);
            while (!sub_packet.empty())
            {
                sub_packet = get_package_value(sub_packet, return_value);
                return_values.push_back(return_value);
            }
        }
        else
        {
            sub_packet_amount = btoi(binary_string.substr(0, 11));
            binary_string = binary_string.substr(11);
            for(int i = 0; i < sub_packet_amount; i++)
            {
                binary_string = get_package_value(binary_string, return_value);
                return_values.push_back(return_value);
            }
        }

        return_value = 0;
        switch(id)
        {
            case 0: for(int64_t i: return_values) 
                        return_value += i; 
                    break;

            case 1: return_value = 1;
                    for(int64_t i: return_values) 
                        return_value *= i; 
                    break;

            case 2: return_value = __INT32_MAX__; 
                    for(int64_t i: return_values) 
                        if(i < return_value) return_value = i;
                    break;
            
            case 3: return_value  = 0; 
                    for(int64_t i: return_values) 
                        if(i > return_value) return_value = i;
                    break;

            case 5: return_value = static_cast<int64_t>(return_values[0] > return_values[1]);
                    break;
            
            case 6: return_value = static_cast<int64_t>(return_values[0] < return_values[1]);
                    break;
            
            case 7: return_value = static_cast<int64_t>(return_values[0] == return_values[1]);
                    break;

            default: break;        
        }

    }
    else
    {
        while(most_sig_bit == "1")
        {
            most_sig_bit = binary_string[0];
            value_string.append(binary_string.substr(1, 4));
            binary_string = binary_string.substr(5);
        }
        return_value = btoi(value_string); 
    }
    
    return binary_string; 
}

int main()
{
    ifstream file("log.txt");
    string in;
    string binary_string;
    int64_t sum = 0;
    getline(file, in);
    
    for(char& c: in)
        binary_string.append(hex_map.find(c)->second);

    get_package_value(binary_string, sum);
    cout << sum << endl;
}