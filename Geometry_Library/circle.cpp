#include "stdafx.h"
#include "circle.h"

Circle::Circle(Point cntr, double rds) :center(cntr), radius(rds), type("Circle") { setEquation(); }

Circle::Circle(double x, double y, double r)
{
	center.x = x;
	center.y = y;
	radius = r;
	type = "Circle";
	setEquation();
}

unsigned int Circle::numberOfCirclesContained(const Circle c1) const
{
	unsigned int timesContained = (getSurface() / c1.getSurface());
	return timesContained;
}

double Circle::getSurface() const
{
	return PI * radius * radius;
}

double Circle::getPerimeter() const
{
	return 2 * PI * radius;
}

bool Circle::containsPoint(Point p) const
{
	GeometricVector vector(center, p);
	return vector.getLength() <= radius;
}

bool Circle::containsPoint(double x, double y) const
{
	Point p(x, y);
	GeometricVector vector(center, p);
	return vector.getLength() <= radius;
}

std::string Circle::getType() const
{
	return type;
}

void Circle::rotate(double radians)
{
	center.rotatePoint(radians);
	setEquation();
}

Ring Circle::getInscribedCircle() const
{
	Ring copyCircle(center, radius);
	return copyCircle;
}

Rectangle Circle::getSurroundingRectangle() const
{
	Point rectSP(center.x - radius, center.y - radius);
	Rectangle surrRectangle(rectSP, 2 * radius, 2 * radius);
	return surrRectangle;
}

//Figure * Circle::create()
//{
//	return new Circle(0, 0, 0);
//}

void Circle::save(std::ostream & out)
{
	out << "Circle " << center.x << " " << center.y << " " << radius << " ";
}

void Circle::load(std::istream & in)
{
	in >> center.x >> center.y >> radius;
}
void Circle::print()
{
	std::cout << "Circle(" << center.x << ", " << center.y << ", " << radius << ")" << std::endl;
}

void Circle::setEquation()
{
	CircleEquation CE(center.x, center.y, radius);
	CircleEq.CE = CE;
	
}
Equation Circle::getEquation() // (x-x0)^2 + (y-y0)^2 = r^2
{
	return CircleEq;
}

std::vector<Point> Circle::IntersectionWithLines(std::vector<LineEquation> sidesLines)
{
	std::vector<Point> intersectionPoints;
	double root1, root2;
	CircleEquation CE = CircleEq.CE;
	for (unsigned int i = 0; i < sidesLines.size(); i++)
	{
		double a = ((sidesLines[i].A / sidesLines[i].B) * (sidesLines[i].A / sidesLines[i].B)) + 1;

		double b = ((-2 * sidesLines[i].A * sidesLines[i].C) / (sidesLines[i].B * sidesLines[i].B)) -
			((2 * sidesLines[i].A * CE.y0) / sidesLines[i].B) - 2 * CE.x0;

		double c = (CE.y0 * CE.y0) -
			(CE.r * CE.r) + (CE.x0 * CE.x0)
			- ((2 * CE.y0 * sidesLines[i].C) / sidesLines[i].B) +
			(sidesLines[i].C * sidesLines[i].C) / (sidesLines[i].B * sidesLines[i].B);
		double discriminant = b * b - 4 * a * c;
		if (discriminant == 0)
		{
			root1 = -b / (2 * a);
			Point p(root1, (-sidesLines[i].A * root1) / sidesLines[i].B + sidesLines[i].C / sidesLines[i].B);
			intersectionPoints.push_back(p);
		}
		else if (discriminant > 0)
		{
			root1 = (-b + sqrt(discriminant)) / (2 * a);
			root2 = (-b - sqrt(discriminant)) / (2 * a);
			Point p(root1, (-sidesLines[i].A * root1) / sidesLines[i].B + sidesLines[i].C / sidesLines[i].B);
			Point q(root2, (-sidesLines[i].A * root2) / sidesLines[i].B + sidesLines[i].C / sidesLines[i].B);
			intersectionPoints.push_back(p);
			intersectionPoints.push_back(q);
		}
	}
	return intersectionPoints;
}
std::vector<Point> Circle::IntersectionWithCircle(CircleEquation otherCE)
{
	CircleEquation CE = CircleEq.CE;
	std::vector<Point> intersectionPoints;
	Point myCenter(CE.x0, CE.y0);
	Point otherCenter(otherCE.x0, otherCE.y0);
	double distanceBetweenCenters, distanceToHeightPrj, height;

	distanceBetweenCenters = myCenter.distance(otherCenter);

	distanceToHeightPrj = (CE.r * CE.r - otherCE.r*otherCE.r +
		distanceBetweenCenters * distanceBetweenCenters) / (2 * distanceBetweenCenters);

	height = sqrt(CE.r * CE.r - distanceToHeightPrj * distanceToHeightPrj);

	Point HeightProjection = otherCenter.sub(myCenter).
		scale(distanceToHeightPrj / distanceBetweenCenters).add(myCenter);

	double x3, y3, x4, y4;
	x3 = HeightProjection.x + height * (otherCenter.y - myCenter.y) / distanceBetweenCenters;
	y3 = HeightProjection.y - height * (otherCenter.x - myCenter.x) / distanceBetweenCenters;
	x4 = HeightProjection.x - height * (otherCenter.y - myCenter.y) / distanceBetweenCenters;
	y4 = HeightProjection.y + height * (otherCenter.x - myCenter.x) / distanceBetweenCenters;

	Point intersectionPoint1(x3, y3), intersectionPoint2(x4, y4);
	intersectionPoints.push_back(intersectionPoint1);
	intersectionPoints.push_back(intersectionPoint2);
	return intersectionPoints;
}

std::vector<Point> Circle::IntersectionWithFigure(Figure * otherFigure)
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