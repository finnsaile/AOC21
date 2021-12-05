#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


/**
 * @brief class contains bingo field and can perform all needed operations on said field
 * 
 */
class BingoFeld
{
    public:
        BingoFeld(ifstream &file);
        int32_t mark_number(int32_t &num);
    private:
        bool check_for_win();
        int32_t calculate_result(int32_t &num);
        int32_t m_feld[5][5];
};

/**
 * @brief Construct a new Bingo Feld:: Bingo Feld object
 * reads from file input and puts values in a 5 x 5 array
 * @param file 
 */
BingoFeld::BingoFeld(ifstream &file)
{
    string in;
    for(int32_t i = 0; i < 5; i++)     
        for(int32_t j = 0; j < 5; j++)
            file >> m_feld[i][j];
}

/**
 * @brief checks if number is present in field and marks it if neccessary 
 * in addition it calls check_for_win and returns the result if needed
 * 
 * @param num 
 * @return int32_t returns -1 if number wasn`t present or if the field didnt win. Else the result is returned.
 */
int32_t BingoFeld::mark_number(int32_t &num)
{
    for(int32_t i = 0; i < 5; i++)
        for(int32_t j = 0; j < 5; j++)
            if(m_feld[i][j] == num)
            {
                m_feld[i][j] = -1;
                if(check_for_win())
                    return calculate_result(num);
            }
        return -1;
}

/**
 * @brief checks if either a full column or a full row is marked 
 * 
 * @return bool returns whether conditions apply and the boars has won 
 */
bool BingoFeld::check_for_win()
{
    int32_t marked_counter_row = 0;
    int32_t marked_counter_col = 0;

    for(int32_t i = 0; i < 5; i++)
    {
        for(int32_t j = 0; j < 5; j++)
        {
            //check columns and rows at the same time and increase counter for each marked value
            if(m_feld[i][j] == -1)
                marked_counter_row += 1;
            if(m_feld[j][i] == -1)
                marked_counter_col += 1; 
        }
        //return true if one row/column is fully marked
        if(marked_counter_col == 5 || marked_counter_row == 5)
            return true;
        else
        {
            //reset counters if not
            marked_counter_col = 0;
            marked_counter_row = 0;
        }
    }

    return false;
}

/**
 * @brief calculates the result by adding up all the unmarked fields and multiplying that value by the last input number
 * 
 * @param num last input number
 * @return int32_t returns the result
 */
int32_t BingoFeld::calculate_result(int32_t &num)
{
    int32_t sum = 0;
    for(int32_t i = 0; i < 5; i++)
    {
        for(int32_t j = 0; j < 5; j++)
            if(m_feld[i][j] != -1)
                sum += m_feld[i][j];
    }

    return num * sum;
}

/**
 * @brief reads the input sequence of numbers, written in the first line of the file, and writes the numbers to a vector
 * 
 * In the file, the numbers are seperated by commas. 
 * These are used to seperate and strip the input string from the file
 * 
 * @param stream target vector
 * @param file input containing numbers
 */
void read_number_stream(vector<int32_t> &stream, ifstream &file)
{
    string in;
    size_t pos = 0;
    //get input string from file
    getline(file, in);

    //iterate over string by finding position of comma
    while((pos = in.find(",")) != string::npos)
    {
        //add everything from beginning of string to comma to vector
        stream.push_back(stoi(in.substr(0, pos)));
        //erase everything up until and including the first comma
        in.erase(0, pos + 1);
    }
    //add remaining number to vector
    stream.push_back(stoi(in));
}

/**
 * @brief calculate the return value of the first winning bingo field
 * 
 * @return int 
 */
int main()
{
    //return value used to determin whether the result has been found
    int32_t return_value = 0;
    ifstream file("log.txt");
    //vector containing all the input numbers
    vector<int32_t>number_vec;
    //vector containing all the bingo fields
    vector<BingoFeld>bingo_feld_vec;
    
    //get numbers from input file
    read_number_stream(number_vec, file);
    //read all the bingo fields and safe them 
    while(!file.eof())
        bingo_feld_vec.push_back(BingoFeld(file));
    file.close();

    //iterate through all the input numbers
    for(auto& number: number_vec)
    {
        //check every bingo field
        for(auto& feld: bingo_feld_vec)
        {   
            return_value = feld.mark_number(number);
            //if field has won output value and terminate programm 
            if(return_value != -1)
            {
                cout << "Result: " << return_value << endl;
                return 0;
            }
        }
    }
        
    //programm wan't successful if nothing gets returned
    return 1;
}