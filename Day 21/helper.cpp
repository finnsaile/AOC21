#include <iostream>

using namespace std;

int main()
{
    for(int i = 1; i < 4; i ++)
    {
        for(int j = 1; j < 4; j++)
        {
            for(int k = 1; k < 4; k++)
                cout << i + j + k << endl;
        }
    }
}