#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

const double TWO_PI = 6.2831853;

// Initial display-window size.
GLsizei winWidth = 400, winHeight = 400;
GLuint regHex;

class screenPt
{
private:
    GLint x, y;
public:
    //Default Constructor: initializes coordinate position to (0, 0).
    screenPt ( ) {
	x = y = 0;
    }
    void setCoords (GLint xCoord, GLint yCoord) {
	x = xCoord;
	y = yCoord;
    }
    GLint getx ( ) const {
	return x;
    }
    GLint gety ( ) const {
	return y;
    }
};

void regHexagon (void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glCallList (regHex);
    glFlush ( );
}

void winReshapeFcn (int newWidth, int newHeight)
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ( );
    gluOrtho2D (0.0, (GLdouble) newWidth, 0.0, (GLdouble) newHeight);
    glClear (GL_COLOR_BUFFER_BIT);
}

// Function to draw a filled regular polygon.
void drawPolygon (int numSides)
{
    screenPt hexVertex, circCtr;
    GLint k, radius = 150;
    GLfloat theta;
    // Specify the vertices of a polygon and draw it.
    circCtr.setCoords (winWidth / 2, winHeight / 2);
    glNewList (regHex, GL_COMPILE);
    glColor3f (rand() % 100 / 100.0, rand() % 100 / 100.0, rand() % 100 / 100.0);  // Set fill color for hexagon to red.
    glBegin (GL_POLYGON);
    for (k = 0; k < numSides; k++) {
    theta = TWO_PI * k / numSides;
    hexVertex.setCoords (circCtr.getx ( ) + radius * cos (theta),
                 circCtr.gety ( ) + radius * sin (theta));
    glVertex2i (hexVertex.getx ( ), hexVertex.gety ( ));
    }
    glEnd ( );
    glEndList ( );
}

// If the mouse is clicked, draw a new polygon with one more side.
void mousePtPlot (GLint button, GLint action, GLint xMouse, GLint yMouse)
{
    static int numSides = 5;
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
    if (numSides < 12)
        numSides++;
    else
        numSides = 5;
    drawPolygon (numSides);
    glutPostRedisplay ( );
    }
}

void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0); // Set display-window color to white.
    regHex = glGenLists (1);
    drawPolygon (5);
}

int main (int argc, char** argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow ("Mouse Plot Points");
    init ( );
    glutDisplayFunc (regHexagon);
    glutReshapeFunc (winReshapeFcn);
    glutMouseFunc (mousePtPlot);
    glutMainLoop ( );
    return 0;
}
