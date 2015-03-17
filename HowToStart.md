#What do you need

# How to start #
If you have bazaar installed on your system, you can get latest sources:

**bzr branch http://cc.oulu.fi/~rantalai/aaplot**

(address changed 6.February 2009)

In Ubuntu you need libglu1-mesa-dev package (for gl.h)

**sudo apt-get install libglu1-mesa-dev**

If you want take screenshots, you need libpng. In Ubuntu:

**sudo apt-get install libpng3-dev**
(depending your ubuntu version, you might must select manually some other package of the given list)

If you do NOT install/have libpng, you must make two changes:

  * In aaplot.h comment the line #define AAPLOT\_SCREENSHOT
  * In Makefile remove -lpng from LDFLAGS=

aaplot has very cool icon and you need libXpm. In Ubuntu:

**sudo apt-get install libxpm-dev**

If you do NOT install/have libxpm-dev, you must make two changes:

  * In aaplot.h comment the line #define AAPLOT\_ICON
  * In Makefile remove -lXpm from LDFLAGS=


Now you can build all examples.

**make all**