#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {

    if (x0 > x1) {
        
        //switch x values
        int temp = x0;
        x0 = x1;
        x1 = temp;
          
        //switch y values 
        temp = y0;
        y0 = y1;
        y1 = temp;
    }

    //incremental counters
    int x = x0;
    int y = y0;

    //vertical lines
    if (x0 == x1) {
        while (y <= y1) {
            plot(s, c, x, y);
            y++;
        }
    }

    //horizontal lines
    else if (y0 == y1) {
        while (x <= x1) {
            plot(s, c, x, y);
            x++;
        }
    }

    //lines with non-zero and non-undefined slopes
    else {

        //A = change in y, B = - change in x
        int A = y1 - y0;
        int B = x0 - x1;

        //lines with positive slope
        if (A > 0) {

            //lines in octant 1 where 0 < slope < 1
            if (A < -B) {

                //line through midpoint of two possible points
                int d = 2 * A + B;
                
                //x always changes, check x faster
                while (x <= x1) {
                    plot(s, c, x, y);
                    
                    //if point is below, increment y and adjust margin of error by making it more -, thus more above the line
                    if (d > 0) {
                        y++;
                        d += 2 * B;
                    }

                    //always increment x and adjust margin by making it more +, more below line
                    x++;
                    d += 2 * A; 
                }
            }

            //lines in octant 2 where slope > 1
            else {
                //reflect over y = x
                int d = A + 2 * B;
                
                //y always changes, check y faster
                while (y <= y1) {
                    plot(s, c, x, y);
                    
                    if (d < 0) {
                        x++;
                        d += 2 * A;
                    }

                    y++;
                    d += 2 * B; 
                }
            }
        }

        else {

            //lines in octant 8 where -1 < m < 0
            if (A > B) {
                
                //reflect over y = 0
                int d = B - 2 * A;

                while (x <= x1) {
                    plot(s, c, x, y);

                    if (d > 0) {
                        y--;
                        d += 2 * B;
                    }

                    x++;
                    d -= 2 * A; //A is now negative so to counter that do -
                } 
            }

            //lines in octant 7 where m < -1
            else {

                //reflect over y = -x
                int d = 2 * B - A;  

                while (y >= y1) {
                    plot(s, c, x, y);

                    if (d < 0) {
                        x++;
                        d -= 2 * A;
                    }

                    y--;
                    d += 2 * B;
                }
            }
        }
    } 
}
