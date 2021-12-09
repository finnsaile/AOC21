#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream file("log.txt");
    string in;
    vector<vector<int32_t>> matrix;
    int32_t sum = 0;

    while (getline(file, in))
    {
        matrix.push_back(vector<int32_t>());
        for(auto& ch: in)
        {
            matrix.back().push_back(ch - '0');
        }
    }
    
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
            if(j < matrix[i].size() - 1 && !(matrix[i][j + 1] > temp_val))
                low = false;

            if(low == true)
            {
                cout << temp_val << endl;
                sum += temp_val + 1;
            }

        }
    }

    file.close();

    cout << sum << endl;
}