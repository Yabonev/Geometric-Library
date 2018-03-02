#ifndef ADDITIONALS_HEADER
#define ADDITIONALS_HEADER
#define PI atan(1) * 4

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
struct Point
{
	double x;
	double y;

	Point(double, double);
	Point();

	void rotatePoint(double);
	bool operator ==(Point) const;
	bool isBetweenTwoPoints(Point, Point);
	double distance(Point);
	Point sub(Point);
	Point add(Point);
	Point scale(double);
	void print();
};



struct LineEquation // Ax + By = C -> y = -A/B*x +C/B
{
public:
	Point sp;
	Point ep;
	double A;
	double B;
	double C;

	LineEquation(Point, Point);
	LineEquation();

	Point LineToLineIntersection(LineEquation);
};

struct CircleEquation 
{
	double x0;
	double y0;
	double r;

	CircleEquation(double, double, double);
	CircleEquation();
};

class Equation
{
public:
	std::vector<LineEquation> LE;
	CircleEquation CE;
	Equation();
};
class GeometricVector
{
public:
	Point sp; // startingPoint
	Point ep; // endingPoint

	GeometricVector(Point, Point);
	double getLength() const;
	double scalarProduct(GeometricVector) const;
};

double smallestNumber(double, double);
double largestNumber(double, double);

#endif // !ADDITIONALS_HEADER
