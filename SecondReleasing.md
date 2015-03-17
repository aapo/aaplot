#Info about second releasing (version 0.2)

---

# THIS PAGE IS ONLY HISTORY #

---


# History #

First  released version 0.1

Second released version 0.2


# What is in aaplot.0.2.tar.gz? #
There are files:
```
aalto2.dat           example_many_curves.c  og_main.c
aalto.dat            example_rings.c        og_menu.c
aaplot.c             example1.c             og_state.c
aaplot_defaults.c    example1P.c            og_structure.c
aaplot_func_list.c   example2.c             og_window.c
aaplot_helper.c      example2P.c            og_callbacks.c         openglut_exp.h
aaplot_point_list.c  example3.c             og_cursor.c            openglut_ext.h
aaplot_screenshot.c  example3P.c            og_display.c           openglut.h
aaplot_table_list.c  example4.c             og_font.c              openglut_std.h
aaplot_window.c      example5.c             og_font_data.c         
                     example_gsl.c          og_font_helper.c
Makefile             example_butterflies.c  og_init.c
                                            og_internal.h

```
  * .dat -files are point-data for (projection of ) 'Aalto-Vase'
see:
![http://tbn0.google.com/images?q=tbn:cQxcwxmAlbqg9M:http://www.iittalahomeshopping.com/WebRoot/iittala/Shops/iittala/4680/EBC8/CD64/5826/CE4C/5274/EB19/D9BC/005100AaltoMalja160Punainen.jpg](http://tbn0.google.com/images?q=tbn:cQxcwxmAlbqg9M:http://www.iittalahomeshopping.com/WebRoot/iittala/Shops/iittala/4680/EBC8/CD64/5826/CE4C/5274/EB19/D9BC/005100AaltoMalja160Punainen.jpg)
  * aaplot`*` -files are this project
  * Makefile makefile
  * example`*` -files are examples
  * og`*` and openglut`*` -files are ripped and modded from openglut see http://openglut.sourceforge.net/


---

# How to use? #
```
make all
or
make example1
(or some other example*)
```

## What is in example file? ##
  * example1: R->R
  * example2: [R2](https://code.google.com/p/aaplot/source/detail?r=2)->R
  * example3: R->[R3](https://code.google.com/p/aaplot/source/detail?r=3) curves
  * example4: file+arrays
  * example5: three windows

  * example1P: R->R,  with parameters
  * example2P: [R2](https://code.google.com/p/aaplot/source/detail?r=2)->R, with parameters
  * example3P: R->[R3](https://code.google.com/p/aaplot/source/detail?r=3), with parameters

nothing new:
  * example\_butterflies: four parameterized curves
  * example\_many\_curves: just many (>20) curves,
  * example\_rings: three rings
  * example\_gsl: aaplot with gsl\_matrix

'make all' will make all except example\_gsl, which uses gsl see: http://www.gnu.org/software/gsl/