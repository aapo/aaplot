CC=cc
CFLAGS=-O2 

LDFLAGS= -L/usr/lib -lpng -lGL -lGLU -lXpm
# -Wall -pedantic -ansi

FILES= Makefile aaplot.c aaplot_defaults.c aaplot_func_list.c aaplot_helper.c aaplot_window.c aaplot_point_list.c aaplot_table_list.c aaplot_screenshot.c aaplot_icon.xpm

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
			
#example_gsl is not part of, because it needs -lgsl
all: example1 example1P example2 example2P example3 example3P example4 example5 example_butterflies example_many_curves example_rings

example1: $(FILES) $(SOURCES) example1.c
	$(CC) $(CFLAGS) $(LDFLAGS) example1.c -o example1
	strip example1
example1P: $(FILES) $(SOURCES) example1P.c
	$(CC) $(CFLAGS) $(LDFLAGS) example1P.c -o example1P
	strip example1P

example2: $(FILES) $(SOURCES) example2.c
	$(CC) $(CFLAGS) $(LDFLAGS) example2.c -o example2
	strip example2
example2P: $(FILES) $(SOURCES) example2P.c
	$(CC) $(CFLAGS) $(LDFLAGS) example2P.c -o example2P
	strip example2P

example3: $(FILES)  $(SOURCES) example3.c
	$(CC) $(CFLAGS) $(LDFLAGS) example3.c -o example3
	strip example3
example3P: $(FILES)  $(SOURCES) example3P.c
	$(CC) $(CFLAGS) $(LDFLAGS) example3P.c -o example3P
	strip example3P

example4: $(FILES)  $(SOURCES) example4.c
	$(CC) $(CFLAGS) $(LDFLAGS)  example4.c -o example4
	strip example4

example5: $(FILES)  $(SOURCES) example5.c
	$(CC) $(CFLAGS) $(LDFLAGS)  example5.c -o example5
	strip example5

example6: $(FILES)  $(SOURCES) example6.c
	$(CC) $(CFLAGS) $(LDFLAGS)  example6.c -o example6
	strip example6

example7: $(FILES)  $(SOURCES) example7.c
	$(CC) $(CFLAGS) $(LDFLAGS)  example7.c -o example7
	strip example7

example_butterflies: $(FILES)  $(SOURCES) example_butterflies.c
	$(CC) $(CFLAGS) $(LDFLAGS)  example_butterflies.c -o example_butterflies
	strip example_butterflies

example_many_curves: $(FILES)  $(SOURCES) example_many_curves.c
	$(CC) $(CFLAGS) $(LDFLAGS)  example_many_curves.c -o example_many_curves
	strip example_many_curves

example_rings: $(FILES)  $(SOURCES) example_rings.c
	$(CC) $(CFLAGS) $(LDFLAGS)  example_rings.c -o example_rings
	strip example_rings

example_gsl: $(FILES)  $(SOURCES) example_gsl.c
	$(CC) $(CFLAGS) -I/usr/include $(LDFLAGS) -lgsl -lgslcblas -lm example_gsl.c -o example_gsl
	strip example_gsl

