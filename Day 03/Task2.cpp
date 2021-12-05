#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    //variables to safe result
    int32_t oxygen, co2;
    //open file
    ifstream file("log.txt");
    string in;
    //vector for storing all binary numbers from input
    vector<string> binary_list_oxygen;
    vector<string> binary_list_co2;

    /**
     * @brief function takes a vector of strings and strips values from it, depending on the most/least common bit in each row
     * 
     * @param binary_list reference to vector<string> containing all the binary numbers
     * @param most_common bool that determines if the most or least common bits should be removed
     * 
     * @return returns the first (and only) element from the stripped list
     */
    auto strip_list = [&](vector<string> &binary_list, bool most_common)
    {   
        //iterate over every "bit" of the string
        for(int32_t i = 0; i < 12; i++)
        {   
            //array to save the amount 0 and 1 have apeared for each iteration, and variable used save most/least common bit
            int32_t bit_counter[2] = {0, 0}, most_sig;

            //traverse vector and count occurences of 0 and 1 in current row
            for(const auto& value: binary_list)
                bit_counter[value[i] - '0'] += 1;

            //determin bit that should not be stripped depending on most_common and the amount of times each bit has occured
            most_sig = most_common ? static_cast<int32_t>(bit_counter[1] >= bit_counter[0]) : static_cast<int32_t>(bit_counter[1] < bit_counter[0]);

            //remove the elements that dont have the given bit at the right position
            //this is done by first using remove_if, which shifts all the "removed" elements to the back,
            //and then returns an iterator to the first removed element.
            //this iterator is then passed to the erase function, which erases every element from said iterator to the end of the vector.
            binary_list.erase(remove_if(binary_list.begin(), binary_list.end(), 
            [&](string s){return !(most_sig == s[i] - '0');}), 
            binary_list.end());

            //break if only one element is left in the vector
            if(binary_list.size() == 1)
               break;
        }
        //retrun the last element
        return binary_list.front();
    };

    /**
     * @brief function takes a string of bits and converts it to a decimal number
     * 
     * @param bit_string string containing the binary number
     * 
     * @return returns the converted decimal number
     */
    auto bit_to_int = [](string bit_string)
    {   
        int32_t sum = 0;
        //convert each bit from the string to an integer and save it in the array
        for(int32_t i = 0; i < bit_string.length(); i++)
            sum += (bit_string[i] - '0') * pow(2, 11 - i);

        //return the sum of all bit-values
        return sum;
    };

    //read input file 
    while(getline(file, in))
    {   
        //add string to vector
        binary_list_oxygen.push_back(in);
        binary_list_co2.push_back(in);
    }
    file.close();

    //call strip_list function on oxygen list. Takes true as 2nd parameter, as the most common bit is the most sigificant bit
    //convert resulting string to int using bit_to_int funbction
    oxygen = bit_to_int(strip_list(binary_list_oxygen, true));
    //same thing for co2 list
    co2 = bit_to_int(strip_list(binary_list_co2, false));

    //output result
    cout << "Oxygen: " << oxygen << "\nCO2: " << co2 << "\nOxygen * CO2 = " << oxygen * co2 << endl;
}