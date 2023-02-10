#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

const double TWO_PI = 6.2831853;

// Initial display-window size.
GLsizei winWidth = 800, winHeight = 800;
GLuint regHex;

class wcPt2D {
  public:
  GLfloat x, y;
};

// Translate the polygon to the specified position.
void translatePolygon (wcPt2D * verts, GLint nVerts, GLfloat tx, GLfloat ty) {
  GLint k;
  for (k = 0; k < nVerts; k++) {
    verts [k].x = verts [k].x + tx;
    verts [k].y = verts [k].y + ty;
  }
  glBegin (GL_POLYGON);
    for (k = 0; k < nVerts; k++)
      glVertex2f (verts [k].x, verts [k].y);
  glEnd ( );
}

// Rotate the polygon about the origin with pivot
void rotatePolygonPiv (wcPt2D * verts, GLint nVerts, wcPt2D pivPt, GLdouble theta) {
  GLint k;
  GLdouble cosTheta = cos (theta);
  GLdouble sinTheta = sin (theta);
  GLdouble x, y;
  for (k = 0; k < nVerts; k++) {
    x = verts [k].x - pivPt.x;
    y = verts [k].y - pivPt.y;
    verts [k].x = pivPt.x + x * cosTheta - y * sinTheta;
    verts [k].y = pivPt.y + x * sinTheta + y * cosTheta;
  }
  glBegin (GL_POLYGON);
    for (k = 0; k < nVerts; k++)
      glVertex2f (verts [k].x, verts [k].y);
  glEnd ( );
}

//Scale the polygon with pivot
void scalePolygon (wcPt2D * verts, GLint nVerts, wcPt2D fixedPt, GLfloat sx, GLfloat sy) {
  GLint k;
  for (k = 0; k < nVerts; k++) {
    verts [k].x = fixedPt.x + sx * (verts [k].x - fixedPt.x);
    verts [k].y = fixedPt.y + sy * (verts [k].y - fixedPt.y);
  }
  glBegin (GL_POLYGON);
    for (k = 0; k < nVerts; k++)
      glVertex2f (verts [k].x, verts [k].y);
  glEnd ( );
}

// Reflect the polygon about the x-axis.
void reflectPolygon (wcPt2D * verts, GLint nVerts, GLfloat x0, GLfloat y0, wcPt2D pivPt)
{
  GLint k;
  GLdouble x, y;
  for (k = 0; k < nVerts; k++) {
    x = verts [k].x - pivPt.x;
    y = verts [k].y - pivPt.y;
    verts [k].x = pivPt.x + x;
    verts [k].y = pivPt.y - y;
  }
  glBegin (GL_POLYGON);
    for (k = 0; k < nVerts; k++)
      glVertex2f (verts [k].x, verts [k].y);
  glEnd ( );
}

// Shear the polygon about the x-axis.
void shearPolygon (wcPt2D * verts, GLint nVerts, GLfloat x0, GLfloat y0, GLfloat shx, GLfloat shy)
{
  GLint k;
  for (k = 0; k < nVerts; k++) {
    verts [k].x = verts [k].x + shx * (verts [k].y - y0);
    verts [k].y = verts [k].y + shy * (verts [k].x - x0);
  }
  glBegin (GL_POLYGON);
    for (k = 0; k < nVerts; k++)
      glVertex2f (verts [k].x, verts [k].y);
  glEnd ( );
}

//Shear the polygon about the y-axis.
void shearPolygonY (wcPt2D * verts, GLint nVerts, GLfloat x0, GLfloat y0, GLfloat shx, GLfloat shy)
{
  GLint k;
  for (k = 0; k < nVerts; k++) {
    verts [k].x = verts [k].x + shx * (verts [k].y - y0);
    verts [k].y = verts [k].y + shy * (verts [k].x - x0);
  }
  glBegin (GL_POLYGON);
    for (k = 0; k < nVerts; k++)
      glVertex2f (verts [k].x, verts [k].y);
  glEnd ( );
}

// Draw a regular pentagon.
void drawPent (wcPt2D * pentVerts, wcPt2D pivotPt) {
  GLint k;
  for (k = 0; k < 5; k++) {
    pentVerts [k].x = 50 * cos (k * TWO_PI / 5);
    pentVerts [k].y = 50 * sin (k * TWO_PI / 5);
  }
  translatePolygon (pentVerts, 5, pivotPt.x, pivotPt.y);
}

// Initialize the vertices for a regular pentagon.
void initPent (wcPt2D * pentVerts, wcPt2D pivotPt) {
  GLint k;
  GLfloat theta;
  for (k = 0; k < 5; k++) {
    theta = TWO_PI * k / 5.0;
    pentVerts [k].x = pivotPt.x + 100 * cos (theta);
    pentVerts [k].y = pivotPt.y + 100 * sin (theta);
  }
}

// Init
void init (void) {
  glClearColor (1.0, 1.0, 1.0, 0.0);
  glColor3f (0.0, 0.0, 1.0);
  glMatrixMode (GL_PROJECTION);
  gluOrtho2D (-250.0, 250.0, -250.0, 250.0);
}

// Display
void displayFcn (void) {
  GLint x = 0, y = 0;
  GLdouble theta = 0.0;
  GLdouble sx = 0.0, sy = 0.0;
  wcPt2D pentVerts [5];
  wcPt2D pivPt;
  GLint nVerts = 5;
  GLint k, choice;
  pivPt.x = 0.0;
  pivPt.y = 0.0;
  glClear (GL_COLOR_BUFFER_BIT);
  glColor3f (0.0, 0.0, 1.0);
  initPent (pentVerts, pivPt);
  drawPent (pentVerts, pivPt);

  //Case 1: Display another polygon to see the effect of translation
  glColor3f (0.0, 1.0, 0.0);
  glPushMatrix ( );
    translatePolygon (pentVerts, nVerts, 120, 120);
  glPopMatrix ( );

  /*Case 2: Display another polygon to see the effect of rotation in other position
  glColor3f (0.5, 0.5, 0.5);
  glPushMatrix ( );
    pivPt.x = 80.0;
    pivPt.y = 80.0;
    rotatePolygonPiv (pentVerts, nVerts, pivPt, 90);
  glPopMatrix ( );*/

  /* Case 3: Display another polygon to see the effect of scaling
  glColor3f (1.0, 0.0, 1.0);
  glPushMatrix ( );
    pivPt.x = 5.0;
    pivPt.y = 5.0;
    scalePolygon (pentVerts, nVerts, pivPt, 1.5, 1.5);
  glPopMatrix ( );*/

  /*Case 4: Display another polygon to see the effect of reflection about x-axis
  glColor3f (1.0, 0.5, 1.0);
  glPushMatrix ( );
    pivPt.x = 50.5;
    pivPt.y = 50.5;
    reflectPolygon (pentVerts, nVerts, 50.0, 50.0, pivPt);
  glPopMatrix ( );*/

  /*Case 5: Display another polygon to see the effect of shear about x-axis
  glColor3f (0.5, 0.5, 1.0);
  glPushMatrix ( );
    shearPolygon (pentVerts, nVerts, 150.0, 150.0, 0.5, 0.5);
  glPopMatrix ( );*/

  /*Case 6: Display another polygon to see the effect of shear about y-axis
  glColor3f (0.5, 0.5, 1.0);
  glPushMatrix ( );
    shearPolygonY (pentVerts, nVerts, -150.0, -150.0, 0.5, 0.5);
  glPopMatrix ( );*/

  glFlush ( );
}

void winReshapeFcn (GLint newWidth, GLint newHeight) {
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ( );
  gluOrtho2D (-250.0, 250.0, -250.0, 250.0);
  glClear (GL_COLOR_BUFFER_BIT);
}

// Main
int main (int argc, char ** argv) {
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition (100, 100);
    glutInitWindowSize (winWidth, winHeight);
  glutCreateWindow ("Polygon Transformations");
  init ( );
  glutDisplayFunc (displayFcn);
  glutReshapeFunc (winReshapeFcn);
  glutMainLoop ( );
  return 0;
}

