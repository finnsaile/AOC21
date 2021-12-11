#include <iostream>
#include <fstream>
#define PART_1
#define N 10

#ifdef PART_2
    #define STEPS 1000
#else
    #define STEPS 100
#endif


using namespace std;
void increase_adjacent(int32_t grid[N][N], int32_t x, int32_t y)
{
    for(int32_t i = -1; i <= 1; i ++)
    {
        for(int32_t j = -1; j <= 1; j++)
        {
            if(x + i >= 0 && x + i < N && y + j >= 0 && y + j < N && grid[x + i][y + j] != 0)
                grid[x + i][y + j]++;
        }
    }
}

int main()
{
    int32_t grid[N][N];
    ifstream file("log.txt");
    string in;
    int32_t flash_count = 0;
    bool flashed = true, all_flashed = true;
    
    for(int32_t i = 0; i < N; i++)
    {
        getline(file, in);
        for(int32_t j = 0; j < N; j++)
            grid[i][j] = in[j] - '0';
    }
    file.close();

    for(int32_t i = 0; i < STEPS; i++)
    {
        for(int32_t i = 0; i < N; i++)
            for(int32_t j = 0; j < N; j++)
                grid[i][j]++;

        flashed = true;
        while(flashed)
        {
            flashed = false;

            for(int32_t i = 0; i < N; i++)
                for(int32_t j = 0; j < N; j++)
                {
                    if(grid[i][j] > 9)
                    {
                        grid[i][j] = 0;
                        flash_count++;
                        increase_adjacent(grid, i, j);
                        flashed = true;
                    }
                }
        }

        #ifdef PART_2
        for(int32_t i = 0; i < N; i++)
        {
            for(int32_t j = 0; j < N; j++)
            {
                if(grid[i][j] != 0)
                    all_flashed = false;
            }
        }
        if(all_flashed == true)
        {
            cout << "All flashed after step: " << i + 1 << endl;
            return 0;
        }
        else
            all_flashed = true;
        #endif
    }

    cout << flash_count << endl;
    return 0;
}