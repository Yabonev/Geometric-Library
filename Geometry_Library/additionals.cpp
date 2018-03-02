#include "stdafx.h"
#include "additionals.h"

GeometricVector::GeometricVector(Point _sp, Point _ep): sp(_sp), ep(_ep){}

double GeometricVector::getLength() const
{
	return sqrt(((ep.x - sp.x) * ((ep.x - sp.x)) + ((ep.y - sp.y) * (ep.y - sp.y))));
}

double GeometricVector::scalarProduct(GeometricVector v) const
{
	return (ep.x - sp.x) * (v.ep.x - v.sp.x) + (ep.y - sp.y) * (v.ep.y - v.sp.y);
}

Point::Point(double _x, double _y) : x(_x), y(_y){}

Point::Point():x(), y() {}

void Point::rotatePoint(double radians)
{	
	Point rotatedPoint(cos(radians) * x - sin(radians) * y,
					   sin(radians) * x + cos(radians) * y);

	x = rotatedPoint.x;
	y = rotatedPoint.y;
}



bool Point::operator==(Point P) const
{
	return x == P.x && y == P.y;
}

bool Point::isBetweenTwoPoints(Point p, Point q)
{
	double minX = smallestNumber(p.x, q.x);
	double minY = smallestNumber(p.y, q.y);
	double maxX = largestNumber(p.x, q.x);
	double maxY = largestNumber(p.y, q.y);
	
	return minX <= x &&
		   x <= maxX &&
		   minY <= y &&
		   y <= maxY;
}

double Point::distance(Point P)
{
	return sqrt((x - P.x)*(x - P.x) + (y - P.y)*(y - P.y));
}

Point Point::sub(Point p2)
{
	return Point(x - p2.x, y - p2.y);
}

Point Point::add(Point p2)
{
	return Point(x + p2.x, y + p2.y);
}

Point Point::scale(double scalar)
{
	return Point(x * scalar, y * scalar);
}

void Point::print()
{
	std::cout << "(" << x << ", " << y << ")  ";
}

double smallestNumber(double x, double y)
{
	if (x <= y)
		return x;

	return y;
}

double largestNumber(double x, double y)
{
	if (x >= y)
		return x;

	return y;
}

LineEquation::LineEquation(Point _sp, Point _ep)
{
	sp = _sp;
	ep = _ep;
	A = ep.y - sp.y;
	B = sp.x - ep.x;
	C = A * sp.x + B * sp.y;
}

Point LineEquation::LineToLineIntersection(LineEquation otherLine)
{	
	Point intersectionPoint; 
	double determinant = A * otherLine.B - B * otherLine.A;
	if (determinant == 0) // parallel lines
	{
		Point linesAreParallel(42.42, 42.42);
		return linesAreParallel;
	}
	else
	{
		intersectionPoint.x = (otherLine.B * C - B * otherLine.C) / determinant;
		intersectionPoint.y = (A * otherLine.C - C * otherLine.A) / determinant;
		if (intersectionPoint.isBetweenTwoPoints(otherLine.sp, otherLine.ep))
			return intersectionPoint;
		else
		{
			Point segmentsDontIntersect(-42.42, -42.42); // lines intersect, but segments dont
			return segmentsDontIntersect;
		}
	}		
}

CircleEquation::CircleEquation(double centerX, double centerY, double radius)
{
	x0 = centerX;
	y0 = centerY;
	r = radius;
}

CircleEquation::CircleEquation() : x0(), y0(), r() {}

Equation::Equation(){}
