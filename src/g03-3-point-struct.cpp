/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  CSci 520, Spring 2022
 * @ide    VSCode Server
 * @date   January 24, 2022
 * @assg   Quick Find
 *
 * @description Sedgwick text, program 3.3 Point data type interface
 */
#include <cmath>
#include <iostream>
using namespace std;


/** point
 *
 * Declaration of a point data type.  A point in our example consists
 * of the x and y position of the point in a 2-dimensional space.
 */
struct Point
{
  float x;
  float y;
}; // the ; is required at end of struct and class declarations


/** distance between points
 * 
 * An example of adding a member function to a point data type.  Here
 * we expect 2 points as inputs to the function, and we calculate the
 * eucledian distance between the two points.
 *
 * @param firstPoint The first point of the pair we need to calculate the
 *   distance between.
 * @param secondPoint The other point of the pair we are calculating the 
 *   distance between.
 * 
 * @returns float Returns the euclidian distance between the firstPoint and
 *   the secondPoint.
 */
float distance(Point firstPoint, Point secondPoint)
{
  float dx = firstPoint.x - secondPoint.x;
  float dy = firstPoint.y - secondPoint.y;
  return sqrt( pow(dx, 2.0) + pow(dy, 2.0) );
}


/** convert to polar coordinates
 *
 * An example of how to return multiple values using reference
 * parameters.  Book shows using pointers, but prefered method
 * for modern C++ is to use reference parameters. Also this 
 * example showed passing in x,y pair separatly, but we continue
 * using our point class.  We could add r and theta fields to the point
 * and convert to polar and save in the structure as an alternative to
 * returning values by reference.
 * 
 * @param point The point we are to convert to polar coordinates.
 * @param r A reference to a float value, we calculate and return the r or
 *   length of the polar coordinate vector.
 * @param theta A reference to a float value, we calculate and return the
 *   theta or angle of the polar coordinate vector in the theta parameter.
 *
 * @returns void No explicit result is returned, but we return the multiple
 *   value results r,theta using the reference parameters to this funcitons.
 */
void polar(Point point, float& r, float& theta)
{
  Point origin;
  origin.x = 0;
  origin.y = 0;
  r = distance(origin, point);
  theta = atan2(point.y, point.x);
}

/** main
 *
 * The main entry point for this program.  Execution of this program
 * will begin with this main function.
 *
 * @param argc The command line argument count which is the number of
 *     command line arguments provided by user when they started
 *     the program.
 * @param argv The command line arguments, an array of character
 *     arrays.
 *
 * @returns An int value indicating program exit status.  Usually 0
 *     is returned to indicate normal exit and a non-zero value
 *     is returned to indicate an error condition.
 */
int main(int argc, char** argv)
{
  // define two points
  Point a;
  Point b;

  // point a is at origin
  a.x = 0;
  a.y = 0;

  // point b is at end of a 3,4,5 triangle
  b.x = 3;
  b.y = 4;

  // calculate distance between the points:
  cout << "(" << a.x << ", " << a.y << ") <-> " 
       << "(" << b.x << ", " << b.y << ") "
       << "distance: " << distance(a, b) << endl;

  // convert point b to polar coordinates, demonstrate passing values by
  // reference
  float r;
  float theta;
  polar(b, r, theta);
  cout << "(" << b.x << ", " << b.y << ")  "
       << " polar coordinates r: " << fixed << r
       << " theta: " << theta << endl;

  // convert radians to degrees
  float degrees = theta * (180.0 / M_PI);
  cout << " degrees: " << degrees << endl;
}
