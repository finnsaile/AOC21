#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ifstream file("log.txt");
    int64_t total_score = 0;
    string in;
    vector<int64_t> scores;
    string completion_string;

    while(getline(file, in))
    {
        stack<char> opening_stack;
        for(char& ch: in)
        {
            if(ch == '(' || ch == '[' || ch == '{' || ch == '<')
                opening_stack.push(ch);
            else if(opening_stack.top() == ch - 1 || opening_stack.top() == ch - 2)
                opening_stack.pop();
            else
                goto skip;
        }

        completion_string.clear();
        while(!opening_stack.empty())
        {
            char temp = opening_stack.top();
            //cout << temp << endl;
            opening_stack.pop();

            if(temp == '(')
                completion_string.push_back(temp + 1);
            else
                completion_string.push_back(temp + 2);
        }
        
        total_score = 0;
        for(char& ch: completion_string)
        {
            int32_t temp_value;
            switch(ch)
            {  
                case ')': temp_value = 1; break;
                case ']': temp_value = 2; break;
                case '}': temp_value = 3; break;
                case '>': temp_value = 4; break;
                default: break;
            }

            total_score *= 5;
            total_score += temp_value;
        }
        scores.push_back(total_score);
        skip:{}
    }

    sort(scores.begin(), scores.end());
    cout << scores.size() << endl;
    file.close();
    cout << scores[scores.size()/2] << endl;
}