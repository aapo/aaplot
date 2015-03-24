CC=cc
CFLAGS=-O2 

LDFLAGS= -L/usr/lib -lpng -lGL -lXpm -Wall -Wextra
# -Wall -pedantic -ansi -Wextra

FILES= aaplot.c aaplot.h aaplot_func_list.c aaplot_helper.c aaplot_window.c aaplot_point_list.c aaplot_table_list.c aaplot_screenshot.c aaplot_inputbox.c aaplot_icon.xpm

SOURCES = og_cursor.c \
			 og_callbacks.c \
			 og_init.c \
			 og_display.c \
			 og_main.c \
			 og_menu.c \
			 og_structure.c \
			 og_state.c \
			 og_font.c \
			 og_font_data.c \
			 og_font_helper.c \
			 og_window.c

glut: $(SOURCES)
	$(CC) $(CFLAGS) -c $(SOURCES)
	ar rvs glut.a *.o


lib: aaplot.a

aaplot.a: $(FILES) $(SOURCES)
	$(CC) $(CFLAGS) -c aaplot.c
	ar rvs aaplot.a aaplot.o

			
#example_gsl is not part of, because it needs -lgsl
all: example1 example1P example2 example2P example3 example3P example4 example5 example6 example7 example_butterflies example_many_curves example_rings

example1: aaplot.a example1.c
	$(CC) $(CFLAGS) $(LDFLAGS) example1.c aaplot.a -o example1 
	strip example1
example1P: aaplot.a example1P.c
	$(CC) $(CFLAGS) $(LDFLAGS) example1P.c aaplot.a -o example1P
	strip example1P

example2: aaplot.a example2.c
	$(CC) $(CFLAGS) $(LDFLAGS) example2.c aaplot.a -o example2
	strip example2
example2P: aaplot.a  example2P.c
	$(CC) $(CFLAGS) $(LDFLAGS) example2P.c aaplot.a -o example2P
	strip example2P

example3: aaplot.a  example3.c
	$(CC) $(CFLAGS) $(LDFLAGS) example3.c aaplot.a -o example3
	strip example3
example3P: aaplot.a example3P.c
	$(CC) $(CFLAGS) $(LDFLAGS) example3P.c aaplot.a -o example3P
	strip example3P

example4: aaplot.a example4.c
	$(CC) $(CFLAGS) $(LDFLAGS)  example4.c aaplot.a -o example4
	strip example4

example5: aaplot.a example5.c
	$(CC) $(CFLAGS) $(LDFLAGS)  example5.c aaplot.a -o example5
	strip example5

example6: aaplot.a example6.c
	$(CC) $(CFLAGS) $(LDFLAGS)  example6.c aaplot.a -o example6
	strip example6

example7: aaplot.a example7.c
	$(CC) $(CFLAGS) $(LDFLAGS)  example7.c aaplot.a -o example7
	strip example7

example_butterflies: aaplot.a example_butterflies.c
	$(CC) $(CFLAGS) $(LDFLAGS)  example_butterflies.c aaplot.a -o example_butterflies
	strip example_butterflies

example_many_curves: aaplot.a example_many_curves.c
	$(CC) $(CFLAGS) $(LDFLAGS)  example_many_curves.c aaplot.a -o example_many_curves
	strip example_many_curves

example_rings: aaplot.a example_rings.c
	$(CC) $(CFLAGS) $(LDFLAGS)  example_rings.c aaplot.a -o example_rings
	strip example_rings

example_gsl: aaplot.a example_gsl.c
	$(CC) $(CFLAGS) -I/usr/include $(LDFLAGS) -lgsl -lgslcblas -lm example_gsl.c aaplot.a  -o example_gsl
	strip example_gsl

