#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <utility>
#include <queue>
#define SIZE 100
using namespace std;

typedef pair<int64_t, int64_t> iPair;

struct Node
{
    Node(int64_t _cost, int64_t _value, iPair _cord) : cost {_cost}, cord {_cord},  value {_value}{}
    int64_t value; 
    int64_t cost;
    iPair cord;
};

struct Comparator
{
    int operator()(const Node& n1, const Node& n2)
    {
        return n1.cost > n2.cost;
    }
};

int64_t dijkstra(vector<vector<Node>>& grid, int64_t max_size)
{
    priority_queue<Node, vector<Node>, Comparator> to_visit;
    int64_t neighbors[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    to_visit.emplace(grid[0][0]);

    while(!to_visit.empty())
    {
        int64_t cost = to_visit.top().cost, x = to_visit.top().cord.first, y = to_visit.top().cord.second;
        to_visit.pop();
        if(x == max_size - 1 && y == max_size - 1)
            return cost;

        for(auto n : neighbors) 
        {
            int64_t new_x = n[0] + x, new_y = n[1] + y;
            if (new_x < 0 || new_x >= max_size || new_y < 0 || new_y >= max_size || grid[new_x][new_y].value == -1)
                continue;

            grid[new_x][new_y].cost = cost + (grid[new_x][new_y].value);

            grid[new_x][new_y].value = -1;
            to_visit.push(grid[new_x][new_y]);
        }
    }

    return -1;
}


int main()
{
    ifstream file("log.txt");
    string in;
    int64_t mult_i, mult_j, temp_value;
    vector<vector<Node>> grid;
    vector<vector<Node>> big_grid;

    for(int64_t i = 0; i < SIZE; i++)
    {
        getline(file, in);
        grid.push_back(vector<Node>());
        for(int64_t j = 0; j < SIZE; j++)
        {
            grid.back().push_back(Node(__INT64_MAX__, in[j] - '0',iPair(i, j)));
        }
    }

    for(int64_t i = 0; i < 5 * SIZE; i++)
    {
        big_grid.push_back(vector<Node>());
        for(int64_t j = 0; j < 5 * SIZE; j++)
        {
            temp_value = grid[i%SIZE][j%SIZE].value + i / SIZE + j / SIZE;
            temp_value = temp_value > 9 ? (temp_value % 10) + 1 : temp_value;
            big_grid.back().push_back(Node(__INT64_MAX__, temp_value, iPair(i, j)));
        }
    }

    grid[0][0].cost = 0;
    big_grid[0][0].cost = 0;

    cout << "Part 1: " << dijkstra(grid, SIZE) << endl;
    cout << "Part 2: " << dijkstra(big_grid, 5 * SIZE) << endl;
    return 0;

}
