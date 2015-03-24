
#include <string.h> /*memset needs*/

/*
 Compute a lookup table of cos and sin values forming a cirle.
    It is the responsibility of the caller to free these tables
    The size of the table is (n+1) to form a connected loop
    The last entry is exactly the same as the first
    The sign of n can be flipped to get the reverse loop
*/
static void ogCircleTable( double **sint, double **cost, const int n )
{
    int i;
    const int size = abs( n );
    double angle;

    /*assert( n );*/
    angle = 2 * M_PI / ( double )n;

    *sint = ( double * )calloc( sizeof( double ), size + 1 );
    *cost = ( double * )calloc( sizeof( double ), size + 1 );

    if( !( *sint ) || !( *cost ) )
    {
        free( *sint );
        free( *cost );
        ogError( "Failed to allocate memory in ogCircleTable" );
    }

    for( i = 0; i < size; i++ )
    {
        ( *sint )[ i ] = sin( angle * i );
        ( *cost )[ i ] = cos( angle * i );
    }

    /* Last sample is duplicate of the first */
    ( *sint )[ size ] = ( *sint )[ 0 ];
    ( *cost )[ size ] = ( *cost )[ 0 ];
}


/*!
    \fn
    \brief    Draw a solid cone.
    \ingroup  geometry
    \param    base       Cone radius at the base in the xy plane.
    \param    height     Height of cone in positive z direction.
    \param    slices     The number of divisions around the z axis. (latitudal)
    \param    stacks     The number of divisions along the z axis. (longitudal)

              The glutSolidCone() function draws a shaded cone
              with a base in the xy-plane, oriented in the positive z
              direction.

    \note     The number of polygons representing the conical surface is
              proportional to (slices*stacks).

    \see      glutWireCone()
*/
void OGAPIENTRY glutSolidCone( GLdouble base, GLdouble height,
                               GLint slices, GLint stacks )
{
    int i, j;
    double DBL_EPSILON =0.001;

    /* Step in z and radius as stacks are drawn. */
    double z0, z1;
    double r0, r1;

    /* Used for computing scaling factors for vertex normals */
    const double side_length = sqrt( height*height + base*base );

    /* Pre-computed circle */
    double *sint = NULL, *cost = NULL;

    if( DBL_EPSILON > base )
        ogWarning( "Small base in glutSolidCone" );
    if( DBL_EPSILON > height )
        ogWarning( "Small height in glutSolidCone" );

    if( 1 > slices )
        ogWarning( "Invalid slices in glutSolidCone" );
    else if( 1 > stacks )
        ogWarning( "Invalid stacks in glutSolidCone" );
    else
        ogCircleTable( &sint, &cost, -slices );

    slices = abs( slices );
    stacks = abs( stacks );

    if( sint && cost && side_length>0.0 )
    {
        const double zStep = height/stacks;
        const double rStep = base/stacks;

        /* Scaling factors for vertex normals */
        const double cosn = height / side_length;
        const double sinn = base   / side_length;

        /* Cover the circular base with a triangle fan... */
        z0 = 0.0;
        z1 = zStep;

        r0 = base;
        r1 = r0 - rStep;

        glBegin( GL_TRIANGLE_FAN );
        glNormal3d( 0.0, 0.0, -1.0 );
        glVertex3d( 0.0, 0.0, z0 );

        for( j = 0; j <= slices; j++ )
            glVertex3d( cost[ j ] * r0, sint[ j ] * r0, z0 );
        glEnd( );

        /* Cover each stack with a quad strip, except the top stack */
        for( i = 0; i < stacks - 1; i++ )
        {
            glBegin( GL_QUAD_STRIP );

            for( j = 0; j <= slices; j++ )
            {
                glNormal3d( cost[ j ] * sinn, sint[ j ] * sinn, cosn );
                glVertex3d( cost[ j ] * r0,   sint[ j ] * r0,   z0   );
                glVertex3d( cost[ j ] * r1,   sint[ j ] * r1,   z1   );
            }

            z0 = z1;
            z1 += zStep;
            r0 = r1;
            r1 -= rStep;
            glEnd( );
        }

        /* The top stack is covered with individual triangles */
        glBegin( GL_TRIANGLES );
        glNormal3d( cost[ 0 ] * sinn, sint[ 0 ] * sinn, cosn );

        for( j = 0; j < slices; j++ )
        {
            glVertex3d( cost[ j + 0 ] * r0,   sint[ j + 0 ] * r0,   z0     );
            glVertex3d( 0,                    0,                    height );
            glNormal3d( cost[ j + 1 ] * sinn, sint[ j + 1 ] * sinn, cosn   );
            glVertex3d( cost[ j + 1 ] * r0,   sint[ j + 1 ] * r0,   z0     );
        }
        glEnd( );
    }

    free( sint );
    free( cost );
}

void init_rotation_matrix(float mo[16])
   {
   memset( mo, 0, sizeof(mo) );
   mo[0]=mo[5]=mo[10]=mo[15]=1;
   }

void update_mo(float mo[16], float angle, float x, float y, float z )
   {
   glPushMatrix();
   glLoadIdentity();
   glMultMatrixf(mo);
   glRotatef( angle, x,y,z );
   glGetFloatv( GL_MODELVIEW_MATRIX, mo );
   glPopMatrix();
   refresh();
   }


/* draws a string of text at position (col,row)
   in window space (upper left corner is (0,0). */
static void draw_text (int col,int row, const char *fmt,float red,float green, float blue)
{
    int viewport[4];

    glGetIntegerv(GL_VIEWPORT,viewport);

    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0,viewport[2],0,viewport[3],-1,1);
    glColor3f(red,green,blue);

        glRasterPos2i(
              glutBitmapWidth(' ') * col,
            - glutBitmapHeight() * (row+2) + viewport[3]
        );

glutBitmapString (fmt);

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}



#ifdef old_get_colors_method
/*
Because random number generator is NOT initialized, this gives same numbers each time when program runs.
All colors will be too 'middle of range', eg. too gray. FIX
*/
void getColors(float *red, float *green, float *blue){
int r=rand ();
float r1=(r+0.0)/RAND_MAX;
//r1 = sqrt(r1);// * r1 *r1 * r1;
r1= r1 /2;


int b=rand ();
if (b>RAND_MAX/2)
  *red=0.5 + r1;
else
  *red=0.5 - r1;
//printf("%lf\n",*red);


r=rand ();
r1=(r+0.0)/RAND_MAX;
//r1 = sqrt(r1);// * r1 *r1 * r1;
r1= r1 /2;

 b=rand ();
if (b>RAND_MAX/2)
  *green=0.5 + r1;
else
  *green=0.5 - r1;
//printf("%lf\n",*green);


r=rand ();
r1=(r+0.0)/RAND_MAX;
//r1 = sqrt(r1);// * r1 *r1 * r1;
r1= r1 /2;


b=rand ();
if (b>RAND_MAX/2)
  *blue=0.5 + r1;
else
  *blue=0.5 - r1;
//printf("%lf\n",*red);


//int g=rand ();
/*int b=rand ();
*blue=(b+0.0)/RAND_MAX;*/

//*red=(r+0.0)/RAND_MAX;
//*green=(g+0.0)/RAND_MAX;
//*blue = *red+*green;
//if (*blue >1.0)
//   *blue=*blue-1.0;

printf("%lf,%lf,%lf\n",*red,*green,*blue);
}
#endif

/*
Because random number generator is NOT initialized, this gives same numbers each time when program runs.
I try generate three numbers [0,1], that all is not approx 0,5.
First I randomize red and green, and if they are 'too middle' I fix blues value.

The point is:
 red   = random value [0,1]
 green = random value [0,1]

There are 4 'slots' which red and green might be.
  0    low     mid=0.5     hig    1
R |     |         |         |     |
G |     |         |         |     |


case 1:
  0    low     mid=0.5     hig    1
R |     |    X    |         |     |
G |     |    X    |         |     |
B |     |         |         |  X  |

case 2:
  0    low     mid=0.5     hig    1
R |     |         |    X    |     |
G |     |         |    X    |     |
B |  X  |         |         |     |

case 3:
  0    low     mid=0.5     hig    1
R |     |         |    X    |     |
G |     |    X    |         |     |
B |  X  |         |         |  X  |

case 4:
  0    low     mid=0.5     hig    1
R |     |    X    |         |     |
G |     |         |    X    |     |
B |  X  |         |         |  X  |

*/
void getColors(float *red, float *green, float *blue){
int r=rand ();
*red=(r+0.0)/RAND_MAX;
int g=rand ();
*green=(g+0.0)/RAND_MAX;

float low = 0.2;
float mid = 0.5;
float hig = 1-low;
if (*red>low && *red<mid && *green>low && *green<mid)
   {
   *blue=(rand()+0.0)/RAND_MAX / (1/low) + hig;
   }
else if (*red>mid && *red<hig && *green>mid && *green<hig)
   {
   *blue=(rand()+0.0)/RAND_MAX / (1/low);
   }
else if (*red>low && *red<hig && *green>low && *green<hig)
   {
   *blue=(rand()+0.0)/RAND_MAX / 2.0;
   int b=rand (); /*toss a coin */
   if (b<RAND_MAX/2)
      *blue=*blue*2 / (1/low);
   else
      *blue=*blue*2 / (1/low) + hig;
   }
else
   {
   int b=rand ();
   *blue=(b+0.0)/RAND_MAX;
   }

/*printf("%lf,%lf,%lf\n",*red,*green,*blue);*/
}
