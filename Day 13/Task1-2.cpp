#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Instruction
{
    Instruction(int32_t value, char direction) : fold_value {value}, fold_direction {direction}
    {}
    int32_t fold_value;
    char fold_direction;
};

struct Point
{
    Point(int32_t x_in, int32_t y_in) : x {x_in}, y {y_in}
    {}
    int32_t x;
    int32_t y;
};

void print_paper(int32_t** paper, int32_t max_x, int32_t max_y)
{
    for(int32_t i = 0; i < max_y; i++)
    {
        for(int32_t j = 0; j < max_x; j++)
        {
            if(paper[i][j] > 0)
                cout << "🟨";
            else 
                cout << "🟥";
        }
        cout << endl;
    }
}


void fold(int32_t** paper, int32_t& max_x, int32_t& max_y, const int32_t& fold_value, const char& fold_direction)
{
    int32_t start_y = 0, start_x = 0, *new_value_ptr;
    if(fold_direction == 'x')
    {
        start_x = fold_value;
        new_value_ptr = &max_x;
    }
    else
    {
        start_y = fold_value;
        new_value_ptr = &max_y;
    }

    for(int32_t i = start_y; i < max_y; i++)
    {
        for(int32_t j = start_x; j < max_x; j++)
        {
            (fold_direction == 'x' ? paper[i][2 * fold_value - j] : paper[2 * fold_value - i][j]) += paper[i][j];
        }
    }
    *new_value_ptr = fold_value;
}

int32_t count_points(int32_t** paper, int32_t max_x, int32_t max_y)
{
    int32_t count = 0;
    for(int32_t i = 0; i < max_y; i++)
    {
        for(int32_t j = 0; j < max_x; j++)
            if(paper[i][j] > 0)
                count++;
    }
    return count;
}

int main()
{
    ifstream file("log.txt");
    int32_t max_x = 0, max_y = 0, pos, delete_size;
    bool read_instructions = false;
    string x_cord, y_cord, in;
    int32_t** paper;
    vector<Point> point_vec;
    vector<Instruction> instruction_vec;

    while(getline(file, in))
    {
        if(in.empty())
        {
            read_instructions = true;
            continue;
        }

        if(!read_instructions)
        {
            pos = in.find(',');
            point_vec.push_back(Point(stoi(in.substr(0, pos)), stoi(in.substr(pos + 1))));
            if(point_vec.back().x > max_x)
                max_x = point_vec.back().x;
            if(point_vec.back().y > max_y)
                max_y = point_vec.back().y;
        }
        else
        {
            pos = in.find('=');
            instruction_vec.push_back(Instruction(stoi(in.substr(pos + 1)), in[pos - 1]));
        }
    }
    file.close();
    max_x++;
    max_y++;
    delete_size = max_y;
    paper = new int32_t*[max_y];
    for(int32_t i = 0; i < max_y; i++)
    {
        paper[i] = new int32_t[max_x];
        for(int j = 0; j < max_x; j++)
            paper[i][j] = 0;
    }

    for(Point& p: point_vec)
        paper[p.y][p.x] = 1;

    for(Instruction& ins: instruction_vec)
        fold(paper, max_x, max_y, ins.fold_value, ins.fold_direction);

    print_paper(paper, max_x, max_y);

    for(int i = 0; i < max_y; i++)
        delete[] paper[i];
    delete[] paper;

    return 0;
}