

/* Input box code adapted from MDDISPLAY:
http://www.structbio.vanderbilt.edu/~mothcw/mddisplay
and distributed openly with permission of Chris Moth, the author
*/
#include <ctype.h>

void (* keyboardInputCompleteCallback)(int lastKey,char *inputString, int id);
int current_entity;

int keyboardWindow = -1;

char* keyboardPromptString;
char keyboardInputString[40];
int keyboardCursorOn=1;


#define minKeyboardTimerKey (10000+100)
#define maxKeyboardTimerKey (minKeyboardTimerKey + 1000)

int keyboardTimerKey = minKeyboardTimerKey;


//////////////////////////



//(isdigit(key))

void inputbox_keyboard_func(unsigned char key,int x, int y)
{
   if (keyboardWindow == -1) // No active inputbox
      {

      }
   else // we are in the middle of active text string input
      {
      int inputChanged = 0;

      unsigned int input_strlen = strlen(keyboardInputString);

      // If ASCII text entered, add it to the keyboard string
      if (isprint(key)
 && input_strlen < sizeof(keyboardInputString)-1)
         {
//       if (islower(key))
//          key = toupper(key);

         keyboardInputString[input_strlen++] = key;
         keyboardInputString[input_strlen] = 0;
         inputChanged = 1;
         }

      // If Backspace entered, wipe out last keystroke.
      if ((key == 8) && // ASCII Backspace
          (input_strlen > 0))
         {
         input_strlen--;
         keyboardInputString[input_strlen] = 0;
         inputChanged = 1;
         }

      // We are "done" if the user presses <ENTER> or <ESC>
      if ((key == 13) || // ASCII Carriage Return
          (key == 27))   // ASCII Escape
         {
         glutDestroyWindow(keyboardWindow);
         keyboardWindow = -1;
         free(keyboardPromptString);
         // This is "your" function that we'll call when user press <ENTER> or <ESC>ape
         keyboardInputCompleteCallback(key,keyboardInputString,current_entity);
         }
      else
      if (inputChanged)
         {
         // We need to redraw the entire text input box when the input
         // has changed through a keystroke or Backspace key.
         int currentWindow = glutGetWindow();

         // Always Turn cursor On when we get a new key or input change!
         // Otherwise, it just does not look right when compared with
         // other GUI text entry routines.
         keyboardCursorOn = 1;
         keyboardTimerKey++; // Ignore pending cursor flip timers
         if (keyboardTimerKey >= maxKeyboardTimerKey)
            keyboardTimerKey = minKeyboardTimerKey;
         glutSetWindow(keyboardWindow);
         glutPostRedisplay();
         glutSetWindow(currentWindow);
         }
      }
}









// I wanted a nice input cursor.  The idea is that when the Timer
// expires, the cursor will flip.  That said, if a new keystroke is pressed
// we want the cursor to appear again, which is handled elsewhere.
void KeyboardTimerFunc(int keyValue)
{
   if ((keyboardWindow != -1) && (keyValue == keyboardTimerKey))
      {
      int currentWindow = glutGetWindow();
      // FlipCursor
      keyboardCursorOn = ! keyboardCursorOn;
      glutSetWindow(keyboardWindow);
      glutPostRedisplay();
      glutSetWindow(currentWindow);
      }

}


void DrawString(int x,int y,char* s) {
glRasterPos2f(x, y);
GLfloat underline_position[4];
   int underline_next = 0;

   while (*s)
      {
      if (*s == '\001') // "Underlined next character"
         {
         glGetFloatv(GL_CURRENT_RASTER_POSITION,underline_position);
         underline_position[1] -= 2; // Drop the y value down a bit for underline
         underline_next = 1;
         }
      else
         {
         if (underline_next) // Then we draw a simple "underline" under this letter first
            {
            glRectf(underline_position[0],
                  underline_position[1],
               underline_position[0]+ glutBitmapWidth(*s),
                  underline_position[1]-1.0);
            underline_next = 0;
            }
         glutBitmapCharacter(*s);
         }
      s++;
      }
}

int StringWidth(const char* s)
{
   int retval = 0;
   while (*s)
      {
      if (*s != '\001') // Don't count underline markers
         retval += glutBitmapWidth(*s);
      s++;
      }

   return retval;
}



// Display the user's text input and the cursor (if keyboardCursorOn)
// Yes, everytime the cursor flips we draw all of this stuff!
void inputbox_display_func(void)
{

   int input_strlen = strlen(keyboardInputString);

   int w = glutGet(GLUT_WINDOW_WIDTH);
   int h = glutGet(GLUT_WINDOW_HEIGHT);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();


   // Reset coordinate System to a simple orthographic 2D system
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glViewport(0,0,w,h);

   //gluOrtho2D(0,w,0,h);
   glOrtho(0,w,0,h,-1,1);

   // Let's have a blue box
   glClearColor(0.0,0.0,1.0,1.0);
   glClear(GL_COLOR_BUFFER_BIT);

   // With a nice white border around it.
   glColor3f(1.0,1.0,1.0);

   glBegin(GL_LINE_LOOP);
      glVertex2i(1,1);
      glVertex2i(w-1,1);
      glVertex2i(w-1,h-1);
      glVertex2i(1,h-1);
   glEnd();

#define nKeyboardWindowOffset 5

   // Draw the "prompt" text
   DrawString(nKeyboardWindowOffset,h-20,keyboardPromptString);


   // Draw any input that the user has entered so far.
   if (input_strlen)
      DrawString(nKeyboardWindowOffset,h-39,keyboardInputString);

   // Draw the underline cursor to the right of the keyboardInputString
   if (keyboardCursorOn)
      {
      int inputWidth = StringWidth(keyboardInputString);
      glRecti(nKeyboardWindowOffset + inputWidth,h-39,inputWidth+15,h-38);
      }

   glutSwapBuffers();

   // Set up cursor flip...
   // 400 msecs seems to feel right, relative to other graphics cursors we see all the time
   keyboardTimerKey++;
   if (keyboardTimerKey >= maxKeyboardTimerKey)
      keyboardTimerKey = minKeyboardTimerKey;
   glutTimerFunc(400,KeyboardTimerFunc,keyboardTimerKey);

}






/* InputBox
Pops out new mini-window with given string.
Takes input and when ready (ESC or ENTER) passes the input to given callback-function.
*/
void input_box_function(char *title, void (* _InputCompleteCallback)(int lastKey,char *inputString, int id), int parent_window, int id)
   {
   // We have an active input going on from another caller... Clean up!
   if (keyboardWindow != -1)
      {
      /* If the user has reselected the same inputbox, just let user proceed with current input (do nothing) */
      if ((keyboardInputCompleteCallback == _InputCompleteCallback) &&
          (! strcmp(keyboardPromptString,title)))
         return;

      // Otherwise, we need to act like the user pressed <ESC> to cancel
      // the current input - because now he wants to input something else.
      glutDestroyWindow(keyboardWindow);
      keyboardWindow = -1;
      free(keyboardPromptString);

      // Pass <ESC> (27) to the Callback function - which will then likely
      // treat the input string as being cancelled.
      keyboardInputCompleteCallback(27,"",-1);
      }

   // Start with an empty input string and the cursor in the on state
   keyboardInputString[0] = 0;
   keyboardCursorOn = 1;
   current_entity=id;

   // This is "your" function that we'll call when the user finally
   // presses <ENTER> or <ESC> to terminate string input
   keyboardInputCompleteCallback = _InputCompleteCallback;
   keyboardPromptString = strdup(title);

   // Compute the least obstrusive size for the text input window, given
   // the input string length, and display that
      {


   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   keyboardWindow = glutCreateSubWindow(
                                    parent_window, //
                                    20,    //x
                                    10,    //y
                                    300,   //width
                                    50);   //height
   }

   glutKeyboardFunc (inputbox_keyboard_func);
   glutDisplayFunc  (inputbox_display_func);
}
