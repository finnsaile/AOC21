#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    //input variables
    fstream file("log.txt");
    string in;

    //Variables to safe current and previous number
    int prev_win, cur_win, count = 0;
    
    //Array to safe all values that are currently inside a window
    int win_values[4];

    //initialise the array with the first 3 elements of the file
    for(int i = 0; i < 3; i++)
    {
        getline(file, in);
        win_values[i] = stoi(in);
    }

    //run untile eof is reached inside
    while(getline(file,in))
    {   
        //read 4th element from file
        win_values[3] = stoi(in);
        //calculate the sums
        prev_win = win_values[0] + win_values[1] + win_values[2];
        cur_win = win_values[1] + win_values[2] + win_values[3];

        //determin whether the current sum is larger than the last
        if(cur_win > prev_win)
            count++;
        
        //shift all values down one slot
        for(int i = 0; i < 3; i++)
            win_values[i] = win_values[i + 1];    
    }

    //close file
    file.close();

    //output total count
    cout << count << endl;
    
    return 0;
}