# History #
  * version 0.1
  * version 0.2
  * version 0.3
  * version 0.4
  * version 0.5
  * version 0.6
  * version 0.7   <---- Current


# What is in aaplot.0.7.tar.gz? #
There are files:
```
aaplot.h                example1.c                 aaglut.h
aaplot.c                example1P.c                aaglut_internal.h
aaplot_func_list.c      example2.c                 aaglut_std.h
aaplot_helper.c         example2P.c                aaglut_exp.h 
aaplot_inputbox.c       example3.c                 aaglut_ext.h 
aaplot_point_list.c     example3P.c                aaglut_callbacks.c        
aaplot_screenshot.c     example4.c                 aaglut_cursor.c        
aaplot_table_list.c     example4P.c                aaglut_display.c 
aaplot_window.c         example5.c                 aaglut_font.c        
                        example5B.c                aaglut_font_data.c 
Makefile                example6.c                 aaglut_font_helper.c
Makefile_win            example7.c                 aaglut_init.c 
Readme                  example8.c                 aaglut_main.c
aaplot_icon.xpm         example_butterflies.c      aaglut_menu.c 
aalto2.dat              example_many_curves.c      aaglut_state.c   
aalto.dat               example_rings.c            aaglut_structure.c     
saucepan.dat            example_gsl.c              aaglut_window.c  
```
  * aalto.dat and aalto2.dat-files are point-data for (projection of ) 'Aalto-Vase'. see: bottom of page
  * saucepan.dat is large 3d-point-data. see: bottom of page
  * aaplot`*` -files are this project
  * example`*` -files are examples
  * aaglut`*` -files are ripped and modded from openglut. see http://openglut.sourceforge.net/
  * Makefile is linux-makefile
  * Makefile\_win is windows-makefile
  * Readme is little manual
  * aaplot\_icon.xpm is icon for applications

---

# How to use? #
```
make all
or
make example1
(or some other example*)
```

## What is in example file? ##
  * example1: R->R functions
  * example2: [R2](https://code.google.com/p/aaplot/source/detail?r=2)->R functions
  * example3: R->[R3](https://code.google.com/p/aaplot/source/detail?r=3) curves
  * example4: [R2](https://code.google.com/p/aaplot/source/detail?r=2)->[R3](https://code.google.com/p/aaplot/source/detail?r=3) curves
  * example5: file+arrays (2d and 3d)
  * example5B: file of 3d-data (saucepan.dat)
  * example6: about user clicked (selected) points
  * example7: three windows
  * example8: changing attributes of functions/tables

  * example1P: R->R,  with parameters
  * example2P: [R2](https://code.google.com/p/aaplot/source/detail?r=2)->R, with parameters
  * example3P: R->[R3](https://code.google.com/p/aaplot/source/detail?r=3), with parameters
  * example4P: [R2](https://code.google.com/p/aaplot/source/detail?r=2)->[R3](https://code.google.com/p/aaplot/source/detail?r=3), with parameters

examples with nothing new:
  * example\_butterflies: four parameterized curves
  * example\_many\_curves: just many (>20) curves,
  * example\_rings: three rings
  * example\_gsl: aaplot with gsl\_matrix

'make all' will make all except example\_gsl, which uses gsl see: http://www.gnu.org/software/gsl/


---

'Aalto-Vase': ![http://tbn0.google.com/images?q=tbn:cQxcwxmAlbqg9M:http://www.iittalahomeshopping.com/WebRoot/iittala/Shops/iittala/4680/EBC8/CD64/5826/CE4C/5274/EB19/D9BC/005100AaltoMalja160Punainen.jpg](http://tbn0.google.com/images?q=tbn:cQxcwxmAlbqg9M:http://www.iittalahomeshopping.com/WebRoot/iittala/Shops/iittala/4680/EBC8/CD64/5826/CE4C/5274/EB19/D9BC/005100AaltoMalja160Punainen.jpg)

'Saucepan': ![http://www.oyonale.com/images/3D/casserole_pov.jpg](http://www.oyonale.com/images/3D/casserole_pov.jpg)