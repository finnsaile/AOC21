#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    //input variables
    ifstream file("log.txt");
    string in;

    //Variables to safe current and previous number
    int prev, cur, count = 0;

    //read first value and store it in current variable
    getline(file, in);
    cur = stoi(in);

    //read new input
    while (getline(file, in))
    {    
        //shift value from current to previous variable
        prev = cur;
        //store new inout
        cur = stoi(in);

        //compare current and previous variable
        if(cur > prev)
            count++;
    }

    //close file
    file.close();

    //outpur total count
    cout << count << endl;
    
}