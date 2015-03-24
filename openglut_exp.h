#ifndef  __OPENGLUT_EXP_H__
#define  __OPENGLUT_EXP_H__

/*
 * openglut_exp.h
 *
 * The experimental interfaces to the OpenGLUT library.
 * Portions copyright (C) 2004, the OpenGLUT project contributors.
 */


#ifdef __cplusplus
extern "C" 
{
#endif


/*
 * GLUT API Extension macro definitions -- display mode
 */
#define GLUT_BORDERLESS                     0x0800

/*
 * OpenGLUT experimental functions.
 */
OGAPI int glutCreateMenuWindow( int parent, int x, int y, int w, int h );

OGAPI void glutSetWindowStayOnTop( int enable );

/*
 * Allow for conditional compilation of experimental features.
 */

#define OPENGLUT_MENUWINDOW
#define OPENGLUT_STAYONTOP

#ifdef __cplusplus
}
#endif

#endif
