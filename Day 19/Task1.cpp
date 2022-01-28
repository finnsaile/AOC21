#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Scanner
{
    Scanner(int32_t _x, int32_t _y, int32_t _z): x{_x}, y{_y}, z{_z}
    {}
    int32_t x;
    int32_t y;
    int32_t z;

    vector<Beacon> beacon_vec;
};

struct Beacon
{
    Beacon(int32_t _x, int32_t _y, int32_t _z): x{_x}, y{_y}, z{_z}
    {}
    int32_t x;
    int32_t y;
    int32_t z;
};

int main()
{
    vector<vector<Beacon>> map;
}
