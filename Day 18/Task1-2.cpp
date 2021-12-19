#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Node
{
    public:
        Node(int32_t _nested_count = 0, int32_t _value = -1);
        ~Node();

        void print_tree();
        void increase_nested_count();
        bool explode();
        bool split();
        int32_t calculate_magnitude();
        Node* left_child = nullptr;
        Node* right_child = nullptr;
        Node* parent = nullptr;
        int32_t value = -1;
        int32_t nested_count = 0;
        static Node* root;
    
    private:
        void add_to_closest();
        void create_value_vec(vector<Node*>&);
};

Node* Node::root = nullptr;

Node::Node(int32_t _nested_count, int32_t _value) : value{_value}, nested_count {_nested_count}
{}

Node::~Node()
{
    delete left_child;
    delete right_child;
}

Node* parse_input(string in, int32_t nested_count)
{
    Node* current_node = new Node(nested_count + 1);
    in = in.substr(1, in.size() - 2);
    bool left_child = true;
    for(char& c: in)
    {
        if(c == '[')
        {
            if(left_child)
            {
                current_node->left_child = new Node(current_node->nested_count + 1);
                current_node->left_child->parent = current_node;
                current_node = current_node->left_child;
            }
            else
            {
                current_node->right_child = new Node(current_node->nested_count + 1);
                current_node->right_child->parent = current_node;
                current_node = current_node->right_child;
            }
            left_child = true;
        }
        else if(c == ',')
        {
            left_child = false;
        }
        else if(c == ']')
        {
            current_node = current_node->parent;
        }
        else
        {
            if(left_child)
            {
                current_node->left_child = new Node(-1, c - '0');
                current_node->left_child->parent = current_node;
            }
            else
            {
                current_node->right_child = new Node(-1, c - '0');
                current_node->right_child->parent = current_node;
            }

        }

    }

    return current_node;
}

void Node::print_tree()
{   
    if(value != -1)
        cout << value << " ";
    if(left_child != nullptr)
        left_child->print_tree();
    if(right_child != nullptr)
        right_child->print_tree();
}

void Node::increase_nested_count()
{   
    if(value == -1)
        nested_count++;
    if(left_child != nullptr)
        left_child->increase_nested_count();
    if(right_child != nullptr)
        right_child->increase_nested_count();
}

bool Node::explode()
{
    if(nested_count == 4 && value == -1)
    {
        add_to_closest();

        if(left_child != nullptr)
        {
            delete left_child;
            left_child = nullptr;
        }
        if(right_child != nullptr)
        {
            delete right_child;     
            right_child = nullptr;   
        }
        value = 0;
        nested_count = -1;
        return true;
    }

    if(left_child != nullptr && left_child->explode())
        return true;
    else if(right_child != nullptr && right_child->explode())
        return true;
    else 
        return false;
}

bool Node::split()
{
    if(value >= 10)
    {
        nested_count = parent->nested_count + 1;
        left_child = new Node(nested_count + 1, value / 2);
        if(value % 2 == 0)
            right_child = new Node(nested_count + 1, value / 2);
        else
            right_child = new Node(nested_count + 1, (value / 2) + 1);

        left_child->parent = this;
        right_child->parent = this;

        value = -1;
        return true;
    }

    if(left_child != nullptr && left_child->split())
        return true;
    else if(right_child != nullptr && right_child->split())
        return true;
    else 
        return false;
}

void Node::add_to_closest()
{
    vector<Node*> value_vec;
    root->create_value_vec(value_vec);

    for(int i = 0; i < value_vec.size(); i++)
    {
        if(value_vec[i] == this->left_child && (i - 1) >= 0)
            value_vec[i - 1]->value += left_child->value;
        if(value_vec[i] == this->right_child && (i + 1) < value_vec.size())
            value_vec[i + 1]->value += right_child->value;
    }
}   

void Node::create_value_vec(vector<Node*>& value_vec)
{
    if(value != -1)
        value_vec.push_back(this);
    else
    {
        if(left_child != nullptr)
            left_child->create_value_vec(value_vec);
        if(right_child != nullptr)
            right_child->create_value_vec(value_vec);
    }
}

int32_t Node::calculate_magnitude()
{
    if(value != -1)
        return value;
    
    return 3 * left_child->calculate_magnitude() + 2 * right_child->calculate_magnitude();
}

int main()
{
    ifstream file("log.txt");
    string in;
    Node* new_root = nullptr;

    getline(file, in);
    Node::root = parse_input(in, -1);
    while(getline(file, in))
    {
        new_root = new Node();
        Node::root->increase_nested_count();
        new_root->left_child = Node::root;
        new_root->left_child->parent = new_root;
        new_root->right_child = parse_input(in, new_root->nested_count);
        new_root->right_child->parent = new_root;
        Node::root = new_root;

        while(true)
        {
            if(Node::root->explode())
            {
                continue;
            }
            else if(Node::root->split())
            {
                continue;
            }
            else 
                break;
        }
    }
    
    cout << "Part 1: " << Node::root->calculate_magnitude() << "\n";
    delete Node::root;
    Node::root = nullptr;

    /*****************************************PART 2*****************************************/

    file.clear();
    file.seekg(0);

    string line1, line2;
    int32_t max_magnitude = 0, temp;
    vector<string> number_string;
 
    while(getline(file, in))
    {
        number_string.push_back(in);
    }

    Node::root = new Node();

    for(int i = 0; i < number_string.size(); i++)
    {
        for(int j = 0; j < number_string.size(); j++)
        {
            line1 = number_string[j];
            line2 = number_string[i];
            Node::root->left_child = parse_input(line1, 0);
            Node::root->left_child->parent = Node::root;
            Node::root->right_child = parse_input(line2, 0);
            Node::root->right_child->parent = Node::root;

            while(true)
            {
                if(Node::root->explode())
                {
                    continue;
                }
                else if(Node::root->split())
                {
                    continue;
                }
                else 
                    break;
            }

            temp = Node::root->calculate_magnitude();
            if(temp > max_magnitude)
                max_magnitude = temp;
            
            delete Node::root->right_child;
            delete Node::root->left_child;
        }
    }

    cout << "Part 2: " << max_magnitude << endl;
}