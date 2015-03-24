CC=cc
CFLAGS=-O2

AAPLOT_FILES=

LDFLAGS= -L/usr/lib  -lGL -lm -lX11 -Wall -Wextra
# -pedantic -ansi

#UnComment if you want ability to take screenshot (by pressing z)
LDFLAGS+=-lpng 
CFLAGS+=-DAAPLOT_SCREENSHOT 

#UnComment if you want icon for application
#LDFLAGS+=-lXpm 
#CFLAGS+=-DAAPLOT_ICON 
#AAPLOT_FILES+=aaplot_icon.xpm



AAPLOT_FILES+= src/aaplot/aaplot.c \
 src/aaplot/aaplot_func_list.c \
 src/aaplot/aaplot_helper.c \
 src/aaplot/aaplot_window.c \
 src/aaplot/aaplot_point_list.c \
 src/aaplot/aaplot_table_list.c \
 src/aaplot/aaplot_screenshot.c \
 src/aaplot/aaplot_inputbox.c

AAGLUT_FILES = src/aaglut/aaglut_cursor.c \
			 src/aaglut/aaglut_callbacks.c \
			 src/aaglut/aaglut_init.c \
			 src/aaglut/aaglut_display.c \
			 src/aaglut/aaglut_main.c \
			 src/aaglut/aaglut_menu.c \
			 src/aaglut/aaglut_structure.c \
			 src/aaglut/aaglut_state.c \
			 src/aaglut/aaglut_font.c \
			 src/aaglut/aaglut_font_data.c \
			 src/aaglut/aaglut_font_helper.c \
			 src/aaglut/aaglut_window.c

		
#example_gsl is not part of, because it needs -lgsl
all: example1 example1P example2 example2P example3 example3P example4 example4P example5 example5B example6 example7 example8 example_butterflies example_many_curves example_rings


lib: aaplot.a

aaplot.a: $(AAPLOT_FILES) $(AAGLUT_FILES)
	$(CC) $(CFLAGS) -c src/aaplot/aaplot.c
	ar rvs aaplot.a aaplot.o


example1: aaplot.a example1.c
	$(CC) $(CFLAGS) example1.c aaplot.a -o example1 $(LDFLAGS)
	strip example1
example1P: aaplot.a example1P.c
	$(CC) $(CFLAGS) example1P.c aaplot.a -o example1P $(LDFLAGS)
	strip example1P

example2: aaplot.a example2.c
	$(CC) $(CFLAGS) example2.c aaplot.a -o example2 $(LDFLAGS)
	strip example2
example2P: aaplot.a  example2P.c
	$(CC) $(CFLAGS) example2P.c aaplot.a -o example2P $(LDFLAGS)
	strip example2P

example3: aaplot.a  example3.c
	$(CC) $(CFLAGS) example3.c aaplot.a -o example3 $(LDFLAGS)
	strip example3
example3P: aaplot.a example3P.c
	$(CC) $(CFLAGS) example3P.c aaplot.a -o example3P $(LDFLAGS)
	strip example3P

example4: aaplot.a example4.c
	$(CC) $(CFLAGS) example4.c aaplot.a -o example4 $(LDFLAGS)
	strip example4
example4P: aaplot.a example4P.c
	$(CC) $(CFLAGS) example4P.c aaplot.a -o example4P $(LDFLAGS)
	strip example4P


example5: aaplot.a example5.c
	$(CC) $(CFLAGS) example5.c aaplot.a -o example5 $(LDFLAGS)
	strip example5
example5B: aaplot.a example5B.c
	$(CC) $(CFLAGS) example5B.c aaplot.a -o example5B $(LDFLAGS)
	strip example5B

example6: aaplot.a example6.c
	$(CC) $(CFLAGS) example6.c aaplot.a -o example6 $(LDFLAGS)
	strip example6

example7: aaplot.a example7.c
	$(CC) $(CFLAGS) example7.c aaplot.a -o example7 $(LDFLAGS)
	strip example7

example8: aaplot.a example8.c
	$(CC) $(CFLAGS) example8.c aaplot.a -o example8 $(LDFLAGS)
	strip example8

example_butterflies: aaplot.a example_butterflies.c
	$(CC) $(CFLAGS) example_butterflies.c aaplot.a -o example_butterflies $(LDFLAGS)
	strip example_butterflies

example_many_curves: aaplot.a example_many_curves.c
	$(CC) $(CFLAGS) example_many_curves.c aaplot.a -o example_many_curves $(LDFLAGS)
	strip example_many_curves

example_rings: aaplot.a example_rings.c
	$(CC) $(CFLAGS) example_rings.c aaplot.a -o example_rings $(LDFLAGS)
	strip example_rings

example_gsl: aaplot.a example_gsl.c
	$(CC) $(CFLAGS) -lgsl -lgslcblas -lm example_gsl.c aaplot.a  -o example_gsl $(LDFLAGS)
	strip example_gsl

clean:
	rm -f aaplot.a
	rm -f aaplot.o
	rm -f example1
	rm -f example1P
	rm -f example2
	rm -f example2P
	rm -f example3
	rm -f example3P
	rm -f example4
	rm -f example4P
	rm -f example5
	rm -f example5B
	rm -f example6
	rm -f example7
	rm -f example8
	rm -f example_butterflies
	rm -f example_many_curves
	rm -f example_rings
