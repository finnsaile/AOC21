#include <iostream>
#include <string>
#include <fstream>

using namespace std;
//struct used to track current direction values
struct MovementDirection
{
    int64_t horizontal;
    int64_t depth;
};

int main()
{
    //arrays to save input string and its substtrings
    string in, split_string[2];
    //struct to save result
    MovementDirection result = {0, 0};
    //variables to save position of substring seperator and input value 
    int32_t space_pos, X;
    
    //open log file
    ifstream file("log.txt");
    
    //read file line by line
    while(getline(file, in))
    {
        //find index of space seperating key and value
        space_pos = in.find(" ");
        //split input string and save both substrings in array
        split_string[0] = in.substr(0, space_pos);
        split_string[1] = in.substr(space_pos + 1);

        //convert value string to int32_t
        X = stoi(split_string[1]);

        //change values in result struct according to input key and value
        if(split_string[0] == "forward")
            result.horizontal += X;
        else if(split_string[0] == "up")
            result.depth -= X;
        else if(split_string[0] == "down")
            result.depth += X;
    }

    //close file
    file.close();
    //output result
    cout << result.horizontal * result.depth << endl;

    return 0;
}