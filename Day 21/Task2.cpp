#include <iostream>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int32_t, int32_t>> rf = {{3, 1}, {4, 3}, {5, 6}, {6, 7}, {7, 6}, {8, 3}, {9, 1}};

pair<int64_t, int64_t> calc_wins(int32_t p1_pos, int32_t p1_score, int32_t p2_pos, int32_t p2_score)
{
    if(p2_score <= 0) return pair<int64_t, int64_t>(0, 1);

    pair<int64_t, int64_t> w(0, 0);

    for(auto& r: rf)
    {
        pair<int64_t, int64_t> c = calc_wins(p2_pos, p2_score, (p1_pos + r.first) % 10, p1_score - 1 - (p1_pos + r.first) % 10);
        w.first = w.first + r.second * c.second;
        w.second = w.second + r.second * c.first;
    }

    return w;
}

int main()
{
    pair<int64_t, int64_t> result = calc_wins(9, 21, 5, 21);
    cout << (result.first < result.second ? result.second : result.first) << endl;
}