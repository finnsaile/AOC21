#include <iostream>

using namespace std;

int main()
{
    int32_t p1_pos = 10 - 1 , p2_pos = 6 - 1, p1_score = 0, p2_score = 0, dice = 0, inc_value;

    while(true)
    {
        inc_value = 3 * dice + 6;
        dice += 3;
        p1_pos = (p1_pos + inc_value) % 10;
        p1_score += p1_pos + 1;
        if(p1_score >= 1000)
            break;

        inc_value = 3 * dice + 6;
        dice += 3;
        p2_pos = (p2_pos + inc_value) % 10;
        p2_score += p2_pos + 1;
        if(p2_score >= 1000)
            break;
    }

    cout << dice * (p2_score < p1_score ? p2_score : p1_score) << endl; 
}