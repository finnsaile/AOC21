#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int main()
{
    //variables to safe result
    int32_t gamma, epsilon;
    //open file
    ifstream file("log.txt");
    string in;
    //array for saving current number of each bit and later on resulting binary number
    int32_t bit_counter[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    /**
     * @brief converts int array of bits to decimal integer value
     * 
     * @param array array containing the bits of the binary number
     * @return returns the decimal value
     */
    auto bit_to_int = [](int32_t* array)
    {
        int32_t sum = 0;
        for(int32_t i = 11; i >= 0; i--)
            sum += array[i] * pow(2, i);

        return sum;
    };

    //read input file 
    while(getline(file, in))
    {   
        //for each binary number, increase number by 0 or 1, depending on bit
        for(int32_t i = 0; i < in.length(); i++)
            bit_counter[i] += in[i] - '0';
    }
    file.close();

    //convert bit counter array to binary number 
    for(int32_t i = 0; i < 12; i++)
        bit_counter[i] = static_cast<int32_t>(bit_counter[i] > 500);


    //convert binary number to decimal
    gamma = bit_to_int(bit_counter);

    //for epsilon, the binary number needs to be inverted. 
    //This is done by converting the number to bool, inverting the bool value and then converting it back to int
    for(int32_t i = 0; i < 12; i++)
        bit_counter[i] = static_cast<int32_t>(!static_cast<bool>(bit_counter[i]));

    //convert new binary number to decimal
    epsilon = bit_to_int(bit_counter);
    
    //output 
    cout << "Gamma: " << gamma << "\nEpsilon: " << epsilon << "\nGamma * Epsilon = " << gamma * epsilon << endl;
}