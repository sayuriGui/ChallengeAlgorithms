#include <iostream>
#include <cmath>

#define fore(i, a, b) for (int i = (a), TT = (b); i < TT; i++)
#define print(s) cout << s << endl

using namespace std;

/*
Create a program that given 2 points in the format (x, y); 
your program will return a list of approximated points that
will represent a line segment
*/

void lineSegment(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double m = dy / dx;
    double b = y1 - m * x1;
    double x = dx / 40;
    double y = dy / 40;
    double x0 = x1;
    double  y0 = y1;

    x0 += x;
    y0 += y;
    int x_Ans = int(x0);
    int y_Ans = int(y0);
    cout << "x: " << int(x0) << " y: " << int(y0)<< endl;
    x0 -+ x;
    y0 -+ y;
    fore(i, 0, 40) {
        x0 += x;
        y0 += y;
        if (x_Ans != int(x0) || y_Ans != int(y0)) {
            y_Ans = int(y0);
            x_Ans = int(x0);
            cout << "x: " << int(x0) << " y: " << int(y0)<< endl;
        }
        
    }
    
}


int main() {
    double x1, y1, x2, y2;
    print ("Enter the first point (x, y): ");
    cin >> x1 >> y1;
    print ("Enter the second point (x, y): ");
    cin >> x2 >> y2;
    lineSegment(x1, y1, x2, y2);
    return 0;
}

