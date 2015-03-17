# aaplot #
<a href='http://www.youtube.com/watch?feature=player_embedded&v=ujbLu7FNSFk' target='_blank'><img src='http://img.youtube.com/vi/ujbLu7FNSFk/0.jpg' width='425' height=344 /></a>


old
| Look Video |
|:-----------|
[![](http://aaplot.googlecode.com/files/aaplot_screenshot1.png)](http://www.youtube.com/watch?v=ujbLu7FNSFk)

aaplot is not stand-alone program. It is library/toolkit which help you to visualize (draw) your mathematical c-functions.

Advantages: No more syntax learning, just c. Some new functions and you are in.

NEW: sources can be used with windows too, see: http://code.google.com/p/aaplot/wiki/windows_MS

# Usage #
Write c-file:
```
#include "aaplot.h"

double f(double x) {
return 3*x*x + 4*x -5;
}

int main(){
 addRFunction(0,&f,0.01,"My Function");
 /* 0   = window number
   &f   = pointer to predefined function
   0.01 = stepping of x 
   "My Function" = just some title
  */
 drawAll();
 return 0;
}
```
Compile (gcc -lXpm -lpng -lGL) and run. You see your function on gl-rendered window.

Look API to see how add different kinds of functions/curves. http://code.google.com/p/aaplot/wiki/API

# Features #
  * Scaling
  * Rotating
  * Zooming
  * Screenshotting (with libpng)
  * Menu
  * Point selecting
  * Coordinate planes (hide/unhide)

  * Printing arrays (2D / 3D)
  * Tables from files (2D / 3D)
  * R->R functions (actually double, not real-number)
  * [R2](https://code.google.com/p/aaplot/source/detail?r=2)->R functions
  * R->[R3](https://code.google.com/p/aaplot/source/detail?r=3) curves
  * [R2](https://code.google.com/p/aaplot/source/detail?r=2)->[R3](https://code.google.com/p/aaplot/source/detail?r=3) curves

Functions and curves with or without parameters.
```
return a*x; /* line */
addRFunctionWithParameters(something);
```



Unlimited functions in one window.
Unlimited windows.

Browse sources online: http://lauta.dyndns.org/aaplot_src/index.html

(almost -ansi -Wall -pedantic)

# Requirements #
_I think easiest way to tell what you need is tell how to install them with Ubuntu._

If you want very latest version of aaplot, you need bazaar.

**sudo apt-get install bzr**

get latest sources:
**bzr branch http://lauta.dyndns.org/aaplot**

You need libglu1-mesa-dev package (for gl.h)

**sudo apt-get install libglu1-mesa-dev**

If you want take screenshots, you need libpng.

**sudo apt-get install libpng3-dev** (depending your ubuntu version, you might must select manually some other package of the given list)


If you want use very cool icon you need libXpm.

**sudo apt-get install libxpm-dev**


---

| Four parameterized curves (the red text is added with gimp). | ![http://aaplot.googlecode.com/files/aaplot_screenshot1.png](http://aaplot.googlecode.com/files/aaplot_screenshot1.png) |
|:-------------------------------------------------------------|:------------------------------------------------------------------------------------------------------------------------|
| Surface and curve. | ![http://aaplot.googlecode.com/files/aaplot_screenshot2.png](http://aaplot.googlecode.com/files/aaplot_screenshot2.png) |
| aaplot 0.5 | ![http://aaplot.googlecode.com/files/aaplot_screenshot3.png](http://aaplot.googlecode.com/files/aaplot_screenshot3.png) |
| Menu: Hide/Unhide grid | ![http://aaplot.googlecode.com/files/aaplot_screenshot4.png](http://aaplot.googlecode.com/files/aaplot_screenshot4.png) |
| Menu: All elements has own settings. | ![http://aaplot.googlecode.com/files/aaplot_screenshot5.png](http://aaplot.googlecode.com/files/aaplot_screenshot5.png) |