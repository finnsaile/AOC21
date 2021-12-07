#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream file("log.txt");
    string in;
    getline(file, in);
    uint64_t fish_count[9], temp, sum = 0;

    for(int32_t i = 0; i < 9; i++)
        fish_count[i] = 0;

    for(char& ch: in)
    {
        if(ch != ',')
            fish_count[ch - '0']++;
    }

    for(int32_t i = 0; i < 256; i++)
    {

        temp = fish_count[0];
        for(int32_t i = 0; i < 8; i++)
        {
            fish_count[i] = fish_count[i + 1];
        }
        fish_count[8] = temp;
        fish_count[6] += temp;
    }

    for(int32_t i = 0; i < 9; i++)
        sum += fish_count[i];

    cout << sum << endl;
    file.close();
}