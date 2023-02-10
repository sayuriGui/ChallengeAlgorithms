#include <GL/glut.h>
#include <iostream>
#include <vector>

using namespace std;

GLsizei winWidth = 400, winHeight = 400;

void init (void)
{
    gluOrtho2D (-100.0, 400, -50.0, 400.0);
}

vector <vector <double>> lineSegment (double x1, double y1, double x2, double y2)
{
    vector <double> points;
    vector <vector <double>> lista;
    double m;
    double dx = x2 - x1;
    double dy = y2 - y1;
    if (dx == 0) {
        m = 0;
    }
    else {
        m = dy / dx;
    }
    double b = y1 - m * x1;
    double x = dx / 30;
    double y = dy / 30;
    double x0 = x1;
    double  y0 = y1;

    int x_Ans = int(x0);
    int y_Ans = int(y0);

    points.push_back(x0);
    points.push_back(y0);
    lista.push_back(points);
    points.clear();
    for (int i = 0; i < 30; i++) {
        x0 += x;
        y0 += y;
        if (x_Ans != int(x0) || y_Ans != int(y0)) {
            y_Ans = int(y0);
            x_Ans = int(x0);
            points.push_back(x0);
            points.push_back(y0);
            lista.push_back(points);
            points.clear();
        }
    }
    return lista;
}

//Draw lines
void drawwLines (void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 1.0);
    glPointSize(5.0);
    glBegin (GL_POINTS);
    vector <vector <double>> lista = lineSegment(1, 2, 100, 20);
    vector <vector <double>> lista2 = lineSegment(10, 200, 50, 10);
    vector <vector <double>> lista3 = lineSegment(300, 300, 10, 10);
    vector <vector <double>> lista4 = lineSegment(200, 300, 250, 50);
    vector <vector <double>> lista5 = lineSegment(350, 350, 100, 300);
    for (int i = 0; i < lista.size(); i++) {
        glVertex2i(lista[i][0], lista[i][1]);
    }
    for (int i = 0; i < lista2.size(); i++) {
        glVertex2i(lista2[i][0], lista2[i][1]);
    }
    for (int i = 0; i < lista3.size(); i++) {
        glVertex2i(lista3[i][0], lista3[i][1]);
    }
    for (int i = 0; i < lista4.size(); i++) {
        glVertex2i(lista4[i][0], lista4[i][1]);
    }
    for (int i = 0; i < lista5.size(); i++) {
        glVertex2i(lista5[i][0], lista5[i][1]);
    }
    glEnd();
    glFlush();
}


int main (int argc, char** argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50, 100);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow ("Challenge 3");
    init();
    glutDisplayFunc (drawwLines);
    glutMainLoop();
    return 0;
}
