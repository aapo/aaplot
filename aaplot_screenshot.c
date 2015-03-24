
/*
Screenshot -> PNG
Copyright (C) 2000 Matthew Danish
Who thanks to Andreas Umbach

*/
#ifdef AAPLOT_SCREENSHOT
#include <stdio.h>


#include<time.h>


static FILE *_fp;

void user_write_data(png_structp png_ptr,
                     png_bytep data, png_size_t length) {
  fwrite(data, length, 1, _fp);
}

void user_flush_data(png_structp png_ptr) {
  fflush(_fp);
}


int shot_number=1;
char time_string[100];

/*
Screenshot name example
200806151809.png
200806151809_00002.png
200806151809_00003.png
200806151809_00004.png
200806151809_00005.png
200806151809_00006.png

First screenshot defines the beginning of the filename (date+time). Second and latest will get suffix.

*/
int PNGScreenShot(int width,int height) {

char *filename;
if (shot_number==1)
   {
   time_t timer;
   timer=time(NULL);
   strftime( time_string, 14, "%Y%m%d%H%M",localtime(&timer)); /*14=max lenght*/  
   char final[18];
   sprintf( final,"%s.png",time_string);
   filename=final;
   shot_number++;
   }
else
   {
   char final[24];
   sprintf( final,"%s_%05d.png",time_string,shot_number); /* %05d = at least five digits, fill with zerous.*/
   filename=final;
   shot_number++;
   }

  
/*printf("screenshot:%d,%d\n",width,height);*/

  int i;
  png_structp png_ptr;
  png_infop info_ptr;
  png_byte **row_pointers;
  unsigned char *data;
  int colortype;

   row_pointers=  malloc(height *sizeof( png_byte *));

   data= malloc(width * height * 3*sizeof( unsigned char ));


  glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

  _fp = fopen(filename, "wb");
   if(!_fp)
     {
     fprintf(stderr, "can't open %s for writing\n", filename);
     return 0;
     }

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);

  if (!png_ptr)
       {
       fclose(_fp);
       return 0;
       }

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
      {
      png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
      fclose(_fp);
      return 0;
      }
  /* png_init_io(png_ptr, _fp); */
  png_set_write_fn(png_ptr, 0, user_write_data, user_flush_data);

  colortype = PNG_COLOR_TYPE_RGB;
  png_set_IHDR(png_ptr, info_ptr, width, height,
               8, colortype, PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png_ptr, info_ptr);

  /* get pointers */
  for(i = 0; i < height; i++)
   {
    row_pointers[i] = data + (height - i - 1)       * 3 * width;

}



  png_write_image(png_ptr, row_pointers);
  png_write_end(png_ptr, info_ptr);
  png_destroy_write_struct(&png_ptr, &info_ptr);

  free(row_pointers);
  free(data);
  fclose(_fp);

  printf("Wrote screenshot to %s\n", filename);

  return 1;


}

#else
int PNGScreenShot(int width,int height) {
printf("Screenshooting is not compiled in.\n");
return -1;
}
#endif
