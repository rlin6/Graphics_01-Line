#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

int main() {

  screen s;
  color c;

  c.red = 0;
  c.green = MAX_COLOR;
  c.blue = 0;

  color a;

  a.red = 0;
  a.green = MAX_COLOR;
  a.blue = MAX_COLOR;

  color b;

  b.red = MAX_COLOR;
  b.green = MAX_COLOR;
  b.blue = MAX_COLOR;

  color d;

  d.red = MAX_COLOR;
  d.green = MAX_COLOR;
  d.blue = 0;

  clear_screen(s);
  
  void koch (int x1, int y1, int x2, int y2, int order) {
    float angle = 60 * M_PI/180;
    
    int x3 = (2 * x1 + x2) / 3;
    int y3 = (2 * y1 + y2) / 3;

    int x4 = (x1 + 2 * x2) / 3;
    int y4 = (y1 + 2 * y2) / 3;

    int x = x3 + (x4 - x3) * cos(angle) + (y4 - y3) * sin(angle);
    int y = y3 - (x4 - x3) * sin(angle) + (y4 - y3) * cos(angle);

    if(order > 0) {
      koch(x1, y1, x3, y3, order - 1);
      koch(x3, y3, x, y, order - 1);
      koch(x, y, x4, y4, order - 1);
      koch(x4, y4, x2, y2, order - 1);
    }

    else {
      draw_line(x1, y1, x3, y3, s, a);
      draw_line(x3, y3, x, y, s, b);
      draw_line(x, y, x4, y4, s, c);
      draw_line(x4, y4, x2, y2, s, d);
    }
  }

  koch(0,0,500,500,5);
  koch(0,500,500,0,5);
  koch(0,500,500,500,5);

  display(s);
  save_extension(s, "lines.png");
}
