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
    int32_t median, sum = 0;

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

    median = (pos_vec[pos_vec.size() / 2 - 1] + pos_vec[pos_vec.size() / 2]) / 2;

    for(int32_t& num: pos_vec)
        sum += (int32_t)abs(num - median);

    cout << sum << endl;
}