#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    ifstream file("log.txt");
    string in;
    getline(file, in);
    vector<int32_t> pos_vec;
    size_t pos;
    int32_t mean = 0, sum_low = 0, sum_up = 0, n;

    //iterate over string by finding position of comma
    while((pos = in.find(",")) != string::npos)
    {
        //add everything from beginning of string to comma to vector
        pos_vec.push_back(stoi(in.substr(0, pos)));
        //erase everything up until and including the first comma
        in.erase(0, pos + 1);
    }
    //add remaining number to vector
    pos_vec.push_back(stoi(in));

    sort(pos_vec.begin(), pos_vec.end());

    for(int32_t& num: pos_vec)
        mean += num;
    mean = mean / 1000;
    
    cout << mean << endl;

    for(int32_t& num: pos_vec)
    {
        n = abs(num - mean);
        sum_low += (n * n + n) / 2;
        n = abs(num - mean + 1);
        sum_up += (n * n + n) / 2;
    }

    cout << (sum_low < sum_up ? sum_low : sum_up) << endl;
}