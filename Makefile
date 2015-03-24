CC=cc
CFLAGS=-O2 

LDFLAGS= -L/usr/lib -lpng -lGL -lGLU 
#-Wall -pedantic -ansi

FILES= Makefile aaplot.c aaplot_defaults.c aaplot_func_list.c aaplot_helper.c aaplot_window.c aaplot_point_list.c aaplot_table_list.c aaplot_screenshot.c

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

SOURCES2 =  og_ext.c \
			 og_font_data.c \
			 og_stroke_roman.c \
			 og_stroke_mono_roman.c \
			 og_gamemode.c \
			 og_geometry.c \
			 og_joystick.c \
			 og_misc.c \
			 og_overlay.c \
			 og_videoresize.c \
			


all: esim1 esim2 esim3 esim4 esim5 esim7 esim8 esim9

esim1: $(FILES) $(SOURCES) esim1.c
	$(CC) $(CFLAGS) $(LDFLAGS) esim1.c -o esim1
	strip esim1

esim2: $(FILES) $(SOURCES) esim2.c
	$(CC) $(CFLAGS) $(LDFLAGS) esim2.c -o esim2
	strip esim2

esim3: $(FILES) $(SOURCES) esim3.c
	$(CC) $(CFLAGS) $(LDFLAGS) esim3.c -o esim3
	strip esim3

esim4: $(FILES) $(SOURCES) esim4.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(SOURCES) esim4.c -o esim4
	strip esim4

esim5: $(FILES) $(SOURCES) esim5.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(SOURCES) esim5.c -o esim5
	strip esim5

esim7: $(FILES) $(SOURCES) esim7.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(SOURCES) esim7.c -o esim7
	strip esim7

esim8: $(FILES) $(SOURCES) esim8.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(SOURCES) esim8.c -o esim8
	strip esim8

esim9: $(FILES) $(SOURCES) esim9.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(SOURCES) esim9.c -o esim9
	strip esim9

