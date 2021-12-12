#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Cave
{
    Cave(string n, bool s) : name{n}, small{s}
    {}

    string name;
    bool small;
    bool visited = false;
    vector<Cave*> paths;
};

int32_t find_cave(string name, vector<Cave*> cave_vec)
{
    for(int32_t i = 0; i < cave_vec.size(); i++)
        if(cave_vec[i]->name == name)
            return i;
            
    return -1;
}

int32_t find_paths(Cave* cave)
{
    int32_t sum = 0;
    if(cave->name == "end")
        return 1;

    if(cave->small && cave->visited)
        return sum;
    else 
        cave->visited = true;

    for(Cave* cv: cave->paths)
            sum += find_paths(cv);

    cave->visited = false;
    return sum;
}



int main()
{
    ifstream file("log.txt");
    string cave_1, cave_2;
    vector<Cave*> cave_vec;
    int32_t cave_index_1, cave_index_2;

    while(getline(file, cave_1, '-') && getline(file, cave_2))
    {   
        if((cave_index_1 = find_cave(cave_1, cave_vec)) == -1)
            cave_vec.push_back(new Cave(cave_1, (bool)islower(cave_1[0])));

        if((cave_index_2 = find_cave(cave_2, cave_vec)) == -1)
            cave_vec.push_back(new Cave(cave_2, (bool)islower(cave_2[0])));

        cave_index_1 = find_cave(cave_1, cave_vec);
        cave_index_2 = find_cave(cave_2, cave_vec);

        cave_vec[cave_index_1]->paths.push_back(cave_vec[cave_index_2]);
        cave_vec[cave_index_2]->paths.push_back(cave_vec[cave_index_1]);
    }

    cout << find_paths(cave_vec[find_cave("start", cave_vec)]) << endl;

    for(auto& p: cave_vec)
        delete p;

    return 0;
}