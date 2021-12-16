#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <utility>
#include <queue>

#define YELLOW "\u001b[33m"
#define RESET "\u001b[0m"

#define SIZE 100

using namespace std;

typedef pair<int64_t, int64_t> iPair;

struct Node
{
    Node(const int64_t _cost, const int64_t _value, const iPair _cord): cost {_cost}, cord {_cord},  value {_value}{}
    int64_t value; 
    int64_t cost;
    iPair cord;
    iPair prev = {-1, -1};
    bool visited = false;
    bool marked = false;

};

struct Comparator
{
    int operator()(const Node& n1, const Node& n2)
    {
        return n1.cost > n2.cost;
    }
};

void print_grid(const vector<vector<Node>>& grid)
{
    for(auto& vec: grid)
    {
        for(auto& node: vec)
        {
            if(node.marked)
                cout << YELLOW << node.value << RESET;
            else
                cout << node.value;
        }
        cout << '\n';
    }
}

int64_t dijkstra(vector<vector<Node>>& grid, const int64_t max_size)
{
    //priority queue (min-heap)
    priority_queue<Node, vector<Node>, Comparator> to_visit;
    //array containing coordinates of potential neighbors
    const int64_t neighbors[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    //mark start
    grid[0][0].marked = true;
    //put start point in queue
    to_visit.emplace(grid[0][0]);

    //runs until queue is empty
    while(!to_visit.empty())
    {
        //get values from element with smallest cost in queue
        const int64_t cost = to_visit.top().cost, x = to_visit.top().cord.first, y = to_visit.top().cord.second;
        //mark node for path drawing
        //grid[x][y].marked = true;
        //remove element from queue
        to_visit.pop();
        // //return cost if end has been reached
        // if(x == max_size - 1 && y == max_size - 1)
        //     return cost;

        //for every possible neighbor of current node
        for(auto n: neighbors) 
        {   
            //calculate coordinates of neighbor
            const int64_t new_x = n[0] + x, new_y = n[1] + y;
            //skip neighbor if node has been marked or if coordinates are out of bound
            if (new_x < 0 || new_x >= max_size || new_y < 0 || new_y >= max_size || grid[new_x][new_y].visited == true)
                continue;

            //set cost of neighbor to current cost plus value of neighbor
            grid[new_x][new_y].cost = cost + (grid[new_x][new_y].value);
            
            //mark neighbor as visited
            grid[new_x][new_y].visited = true;
            grid[new_x][new_y].prev = iPair(x, y);
            //push neighbor into queue
            to_visit.push(grid[new_x][new_y]);
        }
    }

    Node* iter = &grid[max_size - 1][max_size - 1];
    while (iter->cord != iPair(0, 0))
    {   
        auto [x, y] = iter->prev;
        iter->marked = true;
        iter = &grid[x][y];
    }
        
    //return -1 if no path has been found
    return grid[max_size - 1][max_size - 1].cost;
}


int main()
{
    ifstream file("log.txt");
    string in;
    int64_t temp_value;
    vector<vector<Node>> grid;
    vector<vector<Node>> big_grid;

    //read file and create grid for Part 1
    for(int64_t i = 0; i < SIZE; i++)
    {
        getline(file, in);
        grid.push_back(vector<Node>());
        for(int64_t j = 0; j < SIZE; j++)
        {
            grid.back().push_back(Node(0, in[j] - '0', iPair(i, j)));
        }
    }

    //create grid for Task 2 by reading values from grid one 
    for(int64_t i = 0; i < 3 * SIZE; i++)
    {
        big_grid.push_back(vector<Node>());
        for(int64_t j = 0; j < 3 * SIZE; j++)
        {   
            temp_value = grid[i%SIZE][j%SIZE].value + i / SIZE + j / SIZE;
            temp_value = temp_value > 9 ? (temp_value % 10) + 1 : temp_value;
            big_grid.back().push_back(Node(0, temp_value, iPair(i, j)));
        }
    }

    cout << "Part 1: " << dijkstra(grid, SIZE) << '\n';
    print_grid(grid);
    //call function for Part 1 and 2
    cout << "Part 2: " << dijkstra(big_grid, 3 * SIZE) << endl;
    //print_grid(big_grid);
    return 0;

}
