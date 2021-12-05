#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#define N 1000
using namespace std;

void add_line(string in, int32_t map[N][N])
{
    int32_t x1, x2, y1, y2, delta, step_x = 0, step_y = 0;
    sscanf(in.c_str(), "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
    
    if(x1 != x2)
    {
        delta = abs(x1 - x2);
        step_x = (x2 - x1)/delta;
    }

    if(y1 != y2)
    {
        delta = abs(y1 - y2);
        step_y = (y2 - y1)/delta;
    }

    for(int32_t i = 0; i <= delta; i++)
    {
        map[x1][y1]++;
        x1 += step_x;
        y1 += step_y;
    }
}


int main()
{
    ifstream file("log.txt");
    int32_t map[N][N], sum = 0;
    string in;
    for(int32_t i = 0; i < N; i++)
        for(int32_t j = 0; j < N; j++)
            map[i][j] = 0;
 
    while(getline(file, in))
        add_line(in, map);

    for(int32_t i = 0; i < N; i++)
        for(int32_t j = 0; j < N; j++)
            if(map[i][j] > 1)
                sum++;
                
    cout << "Sum: " << sum << endl;
    file.close();
}