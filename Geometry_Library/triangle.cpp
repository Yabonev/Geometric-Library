#include "stdafx.h"
#include "triangle.h"
#include "circle.h"


Triangle::Triangle(Point _A, Point _B, Point _C):A(_A), B(_B), C(_C), type("Triangle")  {setEquation();	}

Triangle::Triangle(double Ax, double Ay, double Bx, double By, double Cx, double Cy)
{
	A.x = Ax;
	A.y = Ay;
	B.x = Bx;
	B.y = By;
	C.x = Cx;
	C.y = Cy;
	type = "Triangle";
	setEquation();
}

double Triangle::getAngleBetweenSides(Point P, Point Q) const
{
	GeometricVector AB(A, B);
	GeometricVector AC(A, C);
	GeometricVector BC(B, C);
	double angle = 0;
	if ((P == A && Q == B) || (P == B && Q == A))
	{
		angle = acos(AC.scalarProduct(BC) / AC.getLength() * BC.getLength());
	}
	else if ((P == A && Q == C) || (P == C && Q == A))
	{
		angle = acos(AB.scalarProduct(BC) / AB.getLength() * BC.getLength());
	}
	else if ((P == C && Q == B) || (P == B && Q == C))
	{
		angle = acos(AC.scalarProduct(AB) / AC.getLength() * AB.getLength());
	}
	return angle;
}	

double Triangle::getSurface() const
{
	return abs(0.5 *((A.x - C.x) * (B.y - A.y) - ((A.x - B.x) * (C.y - A.y))));
}

double Triangle::getPerimeter() const
{
	GeometricVector AB(A, B);
	GeometricVector AC(A, C);
	GeometricVector BC(B, C);

	return AB.getLength() + AC.getLength() + BC.getLength();
}

bool Triangle::containsPoint(Point P) const
{
	Triangle t1(A, B, P);
	Triangle t2(A, C, P);
	Triangle t3(B, C, P);
	return getSurface() == t1.getSurface() + t2.getSurface() + t3.getSurface();
}

bool Triangle::containsPoint(double x, double y) const
{
	Point P(x, y);
	Triangle t1(A, B, P);
	Triangle t2(A, C, P);
	Triangle t3(B, C, P);
	return getSurface() == t1.getSurface() + t2.getSurface() + t3.getSurface();
}

std::string Triangle::getType() const
{
	return type;
}

Point Triangle::getCentroid() const
{
	Point centroid((A.x + B.x + C.x) / 3, (A.y + B.y + C.y) / 3);
	return centroid;
}

void Triangle::rotate(double radians)
{
	A.rotatePoint(radians);
	B.rotatePoint(radians);
	C.rotatePoint(radians);
	setEquation();
}

Ring Triangle::getCircumscribedCircle() const
{	
	double denominator = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
	Point center( ((A.x * A.x + A.y * A.y) * (B.y - C.y) +
				   (B.x * B.x + B.y * B.y) * (C.y - A.y) +
				   (C.x * C.x + C.y * C.y) * (A.y - B.y))  / denominator, 
				  ((A.x * A.x + A.y * A.y) * (C.x - B.x) +
		           (B.x * B.x + B.y * B.y) * (A.x - C.x) +
				   (C.x * C.x + C.y * C.y) * (B.x - A.x)) / denominator);
	GeometricVector AR(A, center);
	double radius = AR.getLength();
	Ring circumscribedCircle(center, radius);
	return circumscribedCircle;
}

Ring Triangle::getInscribedCircle() const
{	
	GeometricVector AB(A, B);
	GeometricVector AC(A, C);
	GeometricVector BC(B, C);
	Point center((BC.getLength() * A.x) + (AC.getLength() * B.x) + (AB.getLength() * C.x) / getPerimeter(),
				 (BC.getLength() * A.y) + (AC.getLength() * B.y) + (AB.getLength() * C.y) / getPerimeter());
	double radius = 2 * getSurface() / getPerimeter();
	Ring inscribedCircle(center, radius);
	return inscribedCircle;
}

Point Triangle::getSurroundingRectangleSP() const
{
	Point rectSP(smallestNumber(A.x, smallestNumber(B.x, C.x)), smallestNumber(A.y, smallestNumber(B.y, C.y)));
	return rectSP;
	/*double rectwidth = largestnumber(a.x, largestnumber(b.x, c.x)) -
					   smallestnumber(a.x, smallestnumber(b.x, c.x));
	double rectheight = largestnumber(a.y, largestnumber(b.y, c.y)) -
						smallestnumber(a.y, smallestnumber(b.y, c.y));
	rectangle surrrectangle(rectsp, rectwidth, rectheight);
	*/
	
}



void Triangle::save(std::ostream & out)
{
	out << "Triangle " << A.x << " " << A.y << " " <<
						  B.x << " " << B.y << " " <<
						  C.x << " " << C.y << " ";
}

void Triangle::load(std::istream & in)
{
	in >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
}
void Triangle::print()
{
	std::cout << "Triangle(" << A.x << ", " << A.y << ", " << B.x << ", " <<
		B.y << ", " << C.x << ", " << C.y << ")" << std::endl;
}
void Triangle::setEquation()
{
	sidesLines.LE.push_back(LineEquation(A, B));
	sidesLines.LE.push_back(LineEquation(B, C));
	sidesLines.LE.push_back(LineEquation(C, A));
}
Equation Triangle::getEquation()
{
	return sidesLines;
}
std::vector<Point> Triangle::IntersectionWithLines(std::vector<LineEquation> linesVector)
{
	std::vector<Point> intersectionPoints;
	for (unsigned int i = 0; i < 3; i++)
	{
		for (unsigned int j = 0; j < linesVector.size(); j++)
		{
			intersectionPoints.push_back(sidesLines.LE[i].LineToLineIntersection(linesVector[j]));
		}
	}
	return intersectionPoints;
}
std::vector<Point> Triangle::IntersectionWithCircle(CircleEquation CE)
{
	std::vector<Point> intersectionPoints;
	double root1, root2;
	for (int i = 0; i < 3; i++)
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

std::vector<Point> Triangle::IntersectionWithFigure(Figure * otherFigure)
{
	Equation otherFigEq = otherFigure->getEquation();
	std::vector<Point> intersectionPoints;
	if (otherFigure->getType() == "Square" ||
		otherFigure->getType() == "Rectangle" ||
		otherFigure->getType() == "Triangle")
	{
		intersectionPoints = IntersectionWithLines(otherFigEq.LE);
	}
	else
	{
		intersectionPoints = IntersectionWithCircle(otherFigEq.CE);
	}
	return intersectionPoints;
}

