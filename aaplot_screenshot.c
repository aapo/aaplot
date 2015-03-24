
/* 
Screenshot -> PNG
Copyright (C) 2000 Matthew Danish
Who thanks to Andreas Umbach 

*/
#ifdef AAPLOT_SCREENSHOT
#include <stdio.h>

static FILE *_fp;

void user_write_data(png_structp png_ptr,
                     png_bytep data, png_size_t length) {
  fwrite(data, length, 1, _fp);
}

void user_flush_data(png_structp png_ptr) {
  fflush(_fp);
}



int PNGScreenShot(int width,int height) {
/*date+time maybe?*/
char *filename="aaplot_screenshot.png";
/*printf("screenshot:%d,%d\n",width,height);*/
  
  int i;
  png_structp png_ptr;
  png_infop info_ptr; 
  png_byte **row_pointers;
  unsigned char *data;
  int colortype;

   row_pointers= (png_byte **) malloc(height *sizeof( png_byte *));

   data= (unsigned char *) malloc(width * height * 3*sizeof( unsigned char ));

  
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
