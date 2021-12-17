#include <iostream>

using namespace std;

int main()
{
    int32_t min_x = 70, max_x = 125, min_y = -159, max_y = -121;
    //int32_t min_x = 20, max_x = 30, min_y = -10, max_y = -5;
    int32_t part_1 = (abs(min_y) - 1) * (abs(min_y))/2;
    cout << part_1 << endl;
    
    int32_t counter = 0;
    for(int32_t x = 0; x <= max_x; x++)
    {
        for(int32_t y = -min_y; y >= min_y; y--)
        {
            int32_t x_cum = 0, y_cum = 0;

            for(int32_t i = 0; x_cum <= max_x && y_cum >= min_y; i++)
            {   
                if(x - i > 0)
                    x_cum += x - i;
                y_cum += y - i;

                if(x_cum >= min_x && x_cum <= max_x && y_cum >= min_y && y_cum <= max_y)
                {
                    counter++;
                    goto l;
                }
            }
            l:{}
        }
        
    }
    cout << counter << endl;
}
