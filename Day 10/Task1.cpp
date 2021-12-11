#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

int main()
{
    ifstream file("log.txt");
    int32_t sum = 0;
    string in;

    stack<char> opening_stack;

    while(getline(file, in))
    {
        for(char& ch: in)
        {
            if(ch == '(' || ch == '[' || ch == '{' || ch == '<')
                opening_stack.push(ch);
            else if(opening_stack.top() == ch - 1 || opening_stack.top() == ch - 2)
                opening_stack.pop();
            else
            {
                switch(ch)
                {   
                    case ')': sum += 3; break;
                    case ']': sum += 57; break;
                    case '}': sum += 1197; break;
                    case '>' : sum += 25137; break;
                    default: break;
                }

                break;
            }
        }
    }

    file.close();
    cout << sum << endl;
}