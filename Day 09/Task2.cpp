#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int32_t calc_basin_size(vector<vector<int32_t>> &matrix, int32_t x, int32_t y)
{
    int32_t value;

    if(x < 0 || y < 0 || x >= matrix.size() || y >= matrix[x].size())
        value = 9;
    else
        value = matrix[x][y];

    if(value == 9)
        return 0;
    else
    {
        matrix[x][y] = 9;
        return 1 + calc_basin_size(matrix, x - 1, y) + calc_basin_size(matrix, x + 1, y) + calc_basin_size(matrix, x, y - 1) + calc_basin_size(matrix, x, y + 1);
    }
        
}

int main()
{
    ifstream file("log.txt");
    string in;
    vector<vector<int32_t>> matrix;
    vector<int32_t> largest_basin;
    int32_t basin_size = 0, product = 1;

    while (getline(file, in))
    {
        matrix.push_back(vector<int32_t>());
        for(auto& ch: in)
        {
            matrix.back().push_back(ch - '0');
        }
    }
    file.close();
    
    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix[i].size(); j++)
        {
            int32_t temp_val = matrix[i][j];
            bool low = true;
            if(i > 0 && !(matrix[i - 1][j] > temp_val))
                low = false;
            if(i < matrix.size() - 1 && !(matrix[i + 1][j] > temp_val))
                low = false;
            if(j > 0 && !(matrix[i][j - 1] > temp_val))
                low = false;
            if(j < matrix[i].size() - 1&& !(matrix[i][j + 1] > temp_val))
                low = false;

            if(low == true)
            {
                basin_size = calc_basin_size(matrix, i, j);
                if(largest_basin.size() < 3)
                    largest_basin.push_back(basin_size);
                else
                {
                    for(auto& value: largest_basin)
                    {
                        if(value < basin_size)
                        {
                            value = basin_size;
                            break;
                        }
                    }
                }
                sort(largest_basin.begin(), largest_basin.end());
            }

        }
    }

    for(auto& value: largest_basin)
        product *= value;

    cout << "Product: " << product << endl;
}