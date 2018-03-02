#include "stdafx.h"
#include "square.h"

Square::Square(Point _sp, double _sideLength)
{
	startingPoint = _sp;
	sideLength = _sideLength;
	type = "Square";
	setEquation();
	
}

Square::Square(double x, double y, double sidelength)
{	
	startingPoint.x = x;
	startingPoint.y = y;
	sideLength = sidelength;
	type = "Square";
	setEquation();
}

double Square::getSideLength() const
{
	return sideLength;
}

double Square::getSurface() const
{
	return sideLength * sideLength;
}

double Square::getPerimeter() const
{
	return 4 * sideLength;
}

bool Square::containsPoint(Point P) const
{
	Point A = startingPoint;
	Point B(A.x + getSideLength(), A.y);
	Point C(A.x + getSideLength(), A.y + getSideLength());
	Point D(A.x , A.y + getSideLength());
	Triangle t1(A, B, P);
	Triangle t2(B, C, P);
	Triangle t3(C, D, P);
	Triangle t4(D, A, P);

	return getSurface() == t1.getSurface() + t2.getSurface() + t3.getSurface() + t4.getSurface();
}

bool Square::containsPoint(double _x, double _y) const
{
	Point P(_x, _y);

	Point A = startingPoint;
	Point B(A.x + getSideLength(), A.y);
	Point C(A.x + getSideLength(), A.y + getSideLength());
	Point D(A.x , A.y + getSideLength());
	Triangle t1(A, B, P);
	Triangle t2(B, C, P);
	Triangle t3(C, D, P);
	Triangle t4(D, A, P);

	return getSurface() == t1.getSurface() + t2.getSurface() + t3.getSurface() + t4.getSurface();
}

std::string Square::getType() const
{
	return type;
}

Point Square::getCentroid() const
{	
	Point D(startingPoint.x + sideLength, startingPoint.y + sideLength);
	Point Centroid(((startingPoint.x + D.x) * 0.5), ((startingPoint.y + D.y) * 0.5));
	return Centroid;
}

void Square::rotate(double radians)
{
	startingPoint.rotatePoint(radians);
	setEquation();
}

Ring Square::getCircumscribedCircle() const
{	
	Point D(startingPoint.x + sideLength, startingPoint.y + sideLength);
	Point centroid(((startingPoint.x + D.x) * 0.5), ((startingPoint.y + D.y) * 0.5));
	GeometricVector Radius(startingPoint, centroid);
	double rds = Radius.getLength();
	Ring circumscribedCircle(centroid, rds);
	return circumscribedCircle;
}

Ring Square::getInscribedCircle() const
{
	Point D(startingPoint.x + sideLength, startingPoint.y + sideLength);
	Point centroid(((startingPoint.x + D.x) * 0.5), ((startingPoint.y + D.y) * 0.5));
	Point B((startingPoint.x + sideLength * 0,5), startingPoint.y);
	GeometricVector radius(B, centroid);
	double rds = radius.getLength();
	Ring inscribedCircle(centroid, rds);
	return inscribedCircle;

}

Rectangle Square::getSurroundingRectangle() const
{
	Rectangle surrRectangle(startingPoint, sideLength, sideLength);
	return surrRectangle;
}

void Square::save(std::ostream & out)
{
	out << "Square " << startingPoint.x << " " << startingPoint.y << " " << sideLength << " ";
}

void Square::load(std::istream & in)
{
	in >> startingPoint.x >> startingPoint.y >> sideLength;
}

void Square::print()
{
	std::cout << "Square(" << startingPoint.x << ", " << startingPoint.y << ", " <<
							   getSideLength() << ")" << std::endl;
}

void Square::setEquation()
{	
	Point A = startingPoint;
	Point B(A.x + getSideLength(), A.y);
	Point C(A.x + getSideLength(), A.y + getSideLength());
	Point D(A.x, A.y + getSideLength());
	sidesLines.LE.push_back(LineEquation(A, B));
	sidesLines.LE.push_back(LineEquation(B, C));
	sidesLines.LE.push_back(LineEquation(C, D));
	sidesLines.LE.push_back(LineEquation(D, A));
}

Equation Square::getEquation()
{
	return sidesLines;
}

std::vector<Point> Square::IntersectionWithLines(std::vector<LineEquation> linesVector)
{
	std::vector<Point> intersectionPoints;
	for (int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < linesVector.size(); j++)
		{
			intersectionPoints.push_back(sidesLines.LE[i].LineToLineIntersection(linesVector[j]));
		}
	}
	return intersectionPoints;
}

std::vector<Point> Square::IntersectionWithCircle(CircleEquation CE)
{	
	std::vector<Point> intersectionPoints;
	double root1, root2;
	for (int i = 0; i < 4; i++)
	{
		double a = ((sidesLines.LE[i].A / sidesLines.LE[i].B) * (sidesLines.LE[i].A / sidesLines.LE[i].B)) + 1;
		double b = ((-2 * sidesLines.LE[i].A * sidesLines.LE[i].C) / (sidesLines.LE[i].B * sidesLines.LE[i].B))
				   - ((2 * sidesLines.LE[i].A * CE.y0) / sidesLines.LE[i].B) - 2 * CE.x0;
		double c = (CE.y0 * CE.y0) - (CE.r * CE.r) + (CE.x0 * CE.x0) - ((2 * CE.y0 * sidesLines.LE[i].C) / sidesLines.LE[i].B) +
			(sidesLines.LE[i].C * sidesLines.LE[i].C) / (sidesLines.LE[i].B * sidesLines.LE[i].B);
		double discriminant = b * b - 4 * a * c;
		if (discriminant == 0)
		{
			root1 = -b / (2 * a);
			Point p(root1, (-sidesLines.LE[i].A * root1) / sidesLines.LE[i].B + sidesLines.LE[i].C / sidesLines.LE[i].B);
			intersectionPoints.push_back(p);
		}
		else if (discriminant > 0)
		{
			root1 = (-b + sqrt(discriminant)) / (2 * a);
			root2 = (-b - sqrt(discriminant)) / (2 * a);
			Point p(root1, (-sidesLines.LE[i].A * root1) / sidesLines.LE[i].B + sidesLines.LE[i].C / sidesLines.LE[i].B);
			Point q(root2, (-sidesLines.LE[i].A * root2) / sidesLines.LE[i].B + sidesLines.LE[i].C / sidesLines.LE[i].B);
			intersectionPoints.push_back(p);
			intersectionPoints.push_back(q);
		}
	}
	return intersectionPoints;
}

std::vector<Point> Square::IntersectionWithFigure(Figure * otherFigure)
{
	Equation otherFigEq = otherFigure->getEquation();
	std::vector<Point> intersectionPoints;
	if (otherFigure->getType() == "Square" ||
		otherFigure->getType() == "Rectangle" ||
		otherFigure->getType() == "Triangle")
	{
	intersectionPoints =  IntersectionWithLines(otherFigEq.LE);
	}
	else
	{
		intersectionPoints = IntersectionWithCircle(otherFigEq.CE);
	}
	return intersectionPoints;
}

