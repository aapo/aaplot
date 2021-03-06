/**
   Bitmap and stroke fonts
*/

#include "aaglut.h"
#include "aaglut_internal.h"

/* -- IMPORT DECLARATIONS -------------------------------------------------- */
#include "aaglut_font_helper.c"
#include "aaglut_font_data.c"


/* -- PRIVATE FUNCTIONS ---------------------------------------------------- */

/*!

only one font is in use. take and return it
*/
static SOG_Font *oghFontByID( ) {
return getFont(); 
}

/*!
    Matches a font ID with a SOG_StrokeFont structure pointer.
    This was changed to match the GLUT header style.
aapo: is this necessary?
*/
static SOG_StrokeFont *oghStrokeByID( void *font )
{
    if( font == GLUT_STROKE_ROMAN      )
        return &ogStrokeRoman;

    ogWarning( "stroke font 0x%08x not found", font );
    return 0;
}

/* -- INTERFACE FUNCTIONS -------------------------------------------------- */

/*!
    \fn
    \brief    Draw a bitmapped character
    \ingroup  bitmapfont
    \param    font      A bitmapped font identifier.
    \param    character A character code.

              Draw a \a character at the current OpenGL raster position
              using a bitmapped \a font.  The raster position is advanced
              by the width of the character.

              Nothing is drawn, and the raster position is unaffected when
              either:
              - \a character is out of range
              - \a font is not a valid OpenGLUT bitmap font
              - The current OpenGL raster position is invalid

    \note     glutBitmapString() is generally more efficient for
              strings of characters.

    \see      glRasterPos(), glutBitmapString(), glutBitmapWidth(),
              glutBitmapHeight(), glutStrokeCharacter()
*/
void OGAPIENTRY glutBitmapCharacter( int character )
{
    const GLubyte *face;
    SOG_Font *f = oghFontByID( );

    if( !f ||
        ( 0 > character ) ||
        (255 < character ) )
        return;

    /* Find the glyph we want to draw. */
    face = f->Characters[ character ];

    glPushClientAttrib( GL_CLIENT_PIXEL_STORE_BIT );

        glPixelStorei( GL_UNPACK_SWAP_BYTES,  GL_FALSE );
        glPixelStorei( GL_UNPACK_LSB_FIRST,   GL_FALSE );
        glPixelStorei( GL_UNPACK_ROW_LENGTH,  0        );
        glPixelStorei( GL_UNPACK_SKIP_ROWS,   0        );
        glPixelStorei( GL_UNPACK_SKIP_PIXELS, 0        );
        glPixelStorei( GL_UNPACK_ALIGNMENT,   1        );
        glBitmap(
            face[ 0 ], f->Height,         /* The bitmap's width and height  */
            f->xorig, f->yorig,           /* The origin in the font glyph   */
            ( float )( face[ 0 ] ), 0.0,  /* The raster advance -- inc. x,y */
            ( face + 1 )                  /* The packed bitmap data...      */
        );

    glPopClientAttrib( );
}

/*!
    \fn
    \brief    Draw a string of bitmapped characters
    \ingroup  bitmapfont
    \param    font    A bitmapped font identifier.
    \param    string  A NUL-terminated ASCII string.

              Draw a \a string the current OpenGL raster position
              using a bitmapped \a font.  The raster position is advanced
              by the width of the string.

              The starting raster position is used as
              the left margin for multi-line strings.
              Each newline character repositions the raster
              position at the beginning of the next line.

              Nothing is drawn, and the raster position is unaffected when
              either:
              - \a font is not a valid OpenGLUT bitmap font
              - \a string is an empty string or NULL pointer
              - The current OpenGL raster position is invalid

    \see      glRasterPos(), glutBitmapCharacter()
*/
void OGAPIENTRY glutBitmapString( const char *string )
{
    SOG_Font *f = oghFontByID( );
    short x = 0;
    unsigned char c;

    if( !f )
        return;

    if( !string || !*string )
        return;

    glPushClientAttrib( GL_CLIENT_PIXEL_STORE_BIT );

    glPixelStorei( GL_UNPACK_SWAP_BYTES,  GL_FALSE );
    glPixelStorei( GL_UNPACK_LSB_FIRST,   GL_FALSE );
    glPixelStorei( GL_UNPACK_ROW_LENGTH,  0        );
    glPixelStorei( GL_UNPACK_SKIP_ROWS,   0        );
    glPixelStorei( GL_UNPACK_SKIP_PIXELS, 0        );
    glPixelStorei( GL_UNPACK_ALIGNMENT,   1        );

    /*
     * Step through the string, drawing each character.
     * A newline will simply translate the next character's insertion
     * point back to the start of the line and down one line.
     */

    while(( c = *string++ )) /*while( c = *string++ ) aapo*/
        if( c == '\n' )
        {
            glBitmap( 0, 0, 0, 0, - ( float ) x, - ( float ) f->Height, NULL );
            x = 0;
        }
        else  /* Not an EOL, draw the bitmap character */
        {
            const GLubyte* face = f->Characters[ c ];
            glBitmap(
                face[ 0 ], f->Height,     /* Bitmap's width and height    */
                f->xorig, f->yorig,       /* The origin in the font glyph */
                face[ 0 ], 0.0,           /* The raster advance; inc. x,y */
                face + 1                  /* The packed bitmap data...    */
            );

            x += face[ 0 ];
        }

    glPopClientAttrib( );
}

/*!
    \fn
    \brief    Return the width of a bitmapped character, in pixels.
    \ingroup  bitmapfont
    \param    font      A bitmapped font identifier.
    \param    character A character code.

              Returns the horizontal OpenGL raster position
              offset for a \a character in a bitmapped \a font.

              It is also an upper bound on the width of the bitmapped glyph
              for \a character, though not all letters will use their full
              width, especially fixed-width fonts.

              Returns 0 if the \a character is out of the inclusive
              range [0,255] or if the \a font is invalid.

    \note     In GLUT, some glyphs could render to the left of the
              starting position, in some fonts.  OpenGLUT's fonts all
              position all of their glyphs to start at, or to the right of,
              the initial position.

    \see      glutBitmapCharacter(), glutBitmapLength(), glutBitmapHeight(),
              glutStrokeWidth()
*/
int OGAPIENTRY glutBitmapWidth( int character )
{
    int ret = 0;
    SOG_Font *f = oghFontByID( );

    if( f &&
        ( 0 <= character ) &&
        ( 256 > character ) )
        ret = *( f->Characters[ character ] );

    return ret;
}

/*!
    \fn
    \brief    Return the width of a bitmapped string, in pixels.
    \ingroup  bitmapfont
    \param    font    A bitmapped font identifier.
    \param    string  A NUL-terminated ASCII string.

              Returns the maximum horizontal OpenGL raster position
              offset for a \a string in a bitmapped \a font.

              As with glutBitmapString(), newlines are taken into
              consideration.

              Returns 0 if the \a font is invalid or if the
              \a string is empty or \a NULL.

    \see      glutBitmapString(), glutBitmapWidth(), glutBitmapHeight(),
        
*/
int OGAPIENTRY glutBitmapLength( const unsigned char *string )
{
    int length = 0, this_line_length = 0;
    SOG_Font *f = oghFontByID( );
    unsigned char c;

    if( f && string )
    {
        while(( c = *string++ ))
            if( c != '\n' ) /* Not an EOL, increment length of line */
                this_line_length += *( f->Characters[ c ]);
            else  /* EOL; reset the length of this line */
            {
                if( length < this_line_length )
                    length = this_line_length;
                this_line_length = 0;
            }
    }

    if ( length < this_line_length )
        length = this_line_length;
    return length;
}

/*!
    \fn
    \brief    Return the height of a given font, in pixels.
    \ingroup  bitmapfont
    \param    font    A bitmapped font identifier.

              Return the line-to-line vertical spacing (in pixels)
              between lines of a bitmapped \a font.

              Returns 0 if \a font is invalid.

    \note     Does <i>not</i> report the height used by individual
              characters.  This may limit its usefulness.  (Compare
              with other font-metric queries.)
    \see      glutBitmapCharacter(), glutBitmapString(), glutBitmapWidth(),
              glutBitmapLength(), glutStrokeHeight()

    \internal
    \todo     We have discussed adding a "font descender" query.
              We should go ahead and do it.
*/
int OGAPIENTRY glutBitmapHeight( )
{
    SOG_Font *f = oghFontByID( );
    int ret = 0;

    if( f )
        ret = f->Height;

    return ret;
}

/*!
    \fn
    \brief    Draw a stroked character.
    \ingroup  fonts
    \param    fontID    A GLUT stroked font identifier.
    \param    character An ASCII character other than NUL.

              This function draws one \a character from one stroked font
              (selected by \a fontID)
              using OpenGL \a GL_LINE_STRIP.  These characters
              are drawn at the origin in model space.
              The model space origin is translated at the end,
              according to the \a character width in \a fontID.

              Does nothing if:
               - The \a fontID is invalid.
               - The \a character is out of the font's range.

    \see      glBegin(), glTranslatef(), glutStrokeWidth(), glutStrokeString(),
              glutStrokeHeight(), glutBitmapCharacter()
*/
void OGAPIENTRY glutStrokeCharacter( void *fontID, int character )
{
    const SOG_StrokeChar *schar;
    const SOG_StrokeStrip *strip;
    int i, j;
    SOG_StrokeFont *font = oghStrokeByID( fontID );

    if( !font ||
        ( 1 > character ) ||
        ( font->Quantity < character ) )
        return;

    schar = font->Characters[ character ];
    if( schar )
    {
        strip = schar->Strips;

        for( i = 0; i < schar->Number; i++, strip++ )
        {
            glBegin( GL_LINE_STRIP );
            for( j = 0; j < strip->Number; j++ )
                glVertex2f( strip->Vertices[ j ].X, strip->Vertices[ j ].Y );
            glEnd( );
        }
        glTranslatef( schar->Right, 0.0, 0.0 );
    }
}

/*!
    \fn
    \brief    Draw a string of stroked characters.
    \ingroup  fonts
    \param    fontID    A GLUT stroked font identifier.
    \param    string    A NUL-terminated ASCII string.

              This function draws a \a string in the font indicated
              by \a fontID.
              It is <i>almost</i> equivalent to calling glutStrokeCharacter()
              on each character in the \a string, successively.
              Mostly, it is a convenience function to hide the loop,
              and to treat \\n as a special symbol rather than a normal
              glyph.

              The first character displays at the current model space
              origin,  The origin changes by successive translations.

              The newline character, \\n (ASCII LF) is treated as
              a newline and resets the origin horizontally
              while advancing the line 1 font-height down the y-axis.

              Does nothing if:
               - \a fontID is out of range.
               - \a string is \a NULL
               - \a string is empty

              Unlike glutBitmapString(), there is little performance
              advantage to using glutStrokeString() as compared with
              calling glutStrokeCharacter() yourself for every
              character.

    \see      glutStrokeCharacter(),
              glutStrokeHeight(), glutBitmapString()
*/
void OGAPIENTRY glutStrokeString( void *fontID, const char *string )
{
    int i, j;
    float length = 0.0;
    SOG_StrokeFont *font = oghStrokeByID( fontID );
    unsigned char c;

    if( font && string )
        /*
         * Step through the string, drawing each character.
         * A newline will simply translate the next character's insertion
         * point back to the start of the line and down one line.
         */
        while(( c = *string++ ))
            if( c < font->Quantity )
            {
                if( c == '\n' )
                {
                    glTranslatef ( -length, -( float )( font->Height ), 0.0 );
                    length = 0.0;
                }
                else  /* Not an EOL, draw the bitmap character */
                {
                    const SOG_StrokeChar *schar =
                        font->Characters[ c ];
                    if( schar )
                    {
                        const SOG_StrokeStrip *strip = schar->Strips;

                        for( i = 0; i < schar->Number; i++, strip++ )
                        {
                            glBegin( GL_LINE_STRIP );
                            for( j = 0; j < strip->Number; j++ )
                                glVertex2f( strip->Vertices[ j ].X,
                                            strip->Vertices[ j ].Y);

                            glEnd( );
                        }

                        length += schar->Right;
                        glTranslatef( schar->Right, 0.0, 0.0 );
                    }
                }
         }
}

/*!
    \fn
    \brief    Returns the width in pixels of a character in a given font.
    \ingroup  fonts
    \param    fontID    A GLUT stroked font identifier.
    \param    character A character code.

              This function reports how far the model space origin will advance
              if you putput this \a character in the font named by \a fontID.
              Not all letters will use their full width, especially in
              fixed-width fonts.

              Returns 0 if \a character is out of range or if the
              \a fontID is invalid.

    \todo     Determine if any glyphs are either wider than this
              function or if they render outside of the bounding
              box given by
              <i>(0,-descent)</i> by <i>(width,height-descent)</i>.
    \note     Historically, this function has been described as
              returning a pixel-width, but was implemented to
              return the width in model-space units, rounded to integers.
              GLUT never resolved this, and freeglut duplicated the
              confusion.
              OpenGLUT has decided to stay in model-space and to
              return the unrounded floating point value.
              An unreleased GLUT 3.8 was supposed to include
              glutStrokeWidthf() and glutStrokeLengthf() (note
              the *f suffixes), but that is not in wide use.
    \see      glutStrokeCharacter(),  glutStrokeHeight()
              glutBitmapWidth()
*/
float OGAPIENTRY glutStrokeWidth( void *fontID, int character )
{
    float ret = 0;
    SOG_StrokeFont *font = oghStrokeByID( fontID );

    if( font &&
        ( 0 < character ) &&
        ( font->Quantity > character ) )
    {
        const SOG_StrokeChar *schar = font->Characters[ character ];
        if( schar )
            ret = schar->Right;
    }

    return ret;
}



/*!
    \fn
    \brief    Returns the height of a given font.
    \ingroup  fonts
    \param    fontID    A GLUT stroked font identifier.

              This function reports the height of a font,
              given by \a fontID,
              as a global characteristic of that font.

              Returns 0 if \a fontID is invalid.

    \note     Does <i>not</i> report the height used by individual
              characters.  This may limit its usefulness; perhaps we
              should change it?  (And/or add a new function.)
    \todo     We have discussed adding a "font descender" query.
              We should go ahead and do it.
    \see      glutStrokeCharacter(), glutStrokeString(), glutStrokeWidth(),
              glutBitmapHeight()
*/
GLfloat OGAPIENTRY glutStrokeHeight( void *fontID )
{
    GLfloat ret = 0;
    SOG_StrokeFont *font = oghStrokeByID( fontID );

    if( font )
        ret = font->Height;

    return ret;
}
