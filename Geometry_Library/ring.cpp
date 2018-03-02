#include "stdafx.h"
#include "ring.h"

Ring::Ring(Point cntr, double rds) :center(cntr), radius(rds), type("Ring") { setEquation(); }

Ring::Ring(double x, double y, double r)
{
	center.x = x;
	center.y = y;
	radius = r;
	type = "Ring";
	setEquation();
}

Ring::Ring():center(), radius(), type("Ring"){ setEquation(); }

double Ring::getSurface() const
{
	return 0;
}

double Ring::getPerimeter() const
{
	return 2 * PI * radius;
}

bool Ring::containsPoint(Point p) const
{
	GeometricVector vector(center, p);
	return vector.getLength() == radius;
}

bool Ring::containsPoint(double x, double y) const
{
	Point p(x, y);
	GeometricVector vector(center, p);
	return vector.getLength() == radius;
}

std::string Ring::getType() const
{
	return type;
}

void Ring::rotate(double radians)
{
	center.rotatePoint(radians);
	setEquation();
}

Ring Ring::getInscribedCircle() const
{
	Ring copyCircle(center, radius);
	return copyCircle;
}

Point Ring::getSurroundingRectangleSP() const
{	
	Point rectSP(center.x - radius, center.y - radius);
	return rectSP;
}



void Ring::save(std::ostream & out)
{
	out << "Ring " << center.x << " " << center.y << " " << radius << " ";
}

void Ring::load(std::istream & in)
{
	in >> center.x >> center.y >> radius;
}
void Ring::print()
{
	std::cout << "Ring(" << center.x << ", " << center.y << ", " << radius << ")" << std::endl;
}

void Ring::setEquation()
{
	CircleEq.CE.x0 = center.x;
	CircleEq.CE.y0 = center.y;
	CircleEq.CE.r = radius;
}
Equation Ring::getEquation() // (x-x0)^2 + (y-y0)^2 = r^2
{
	return CircleEq;
}

std::vector<Point> Ring::IntersectionWithLines(std::vector<LineEquation> sidesLines)
{
	std::vector<Point> intersectionPoints;
	double root1, root2;
	for (unsigned int i = 0; i < sidesLines.size(); i++)
	{
		double a = ((sidesLines[i].A / sidesLines[i].B) * (sidesLines[i].A / sidesLines[i].B)) + 1;

		double b = ((-2 * sidesLines[i].A * sidesLines[i].C) / (sidesLines[i].B * sidesLines[i].B))	-	
				   (( 2 * sidesLines[i].A * CircleEq.CE.y0) / sidesLines[i].B) - 2 * CircleEq.CE.x0;

		double c = (CircleEq.CE.y0 * CircleEq.CE.y0) - 
			(CircleEq.CE.r * CircleEq.CE.r) + (CircleEq.CE.x0 * CircleEq.CE.x0)
			- ((2 * CircleEq.CE.y0 * sidesLines[i].C) / sidesLines[i].B) +
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
std::vector<Point> Ring::IntersectionWithCircle(CircleEquation otherCE) 
{
	std::vector<Point> intersectionPoints;
	Point myCenter(CircleEq.CE.x0, CircleEq.CE.y0);
	Point otherCenter(otherCE.x0, otherCE.y0);
	double distanceBetweenCenters, distanceToHeightPrj, height;

	distanceBetweenCenters = myCenter.distance(otherCenter);

	distanceToHeightPrj = (CircleEq.CE.r * CircleEq.CE.r - otherCE.r*otherCE.r +	
	distanceBetweenCenters * distanceBetweenCenters)/ (2 * distanceBetweenCenters);

	height = sqrt(CircleEq.CE.r * CircleEq.CE.r - distanceToHeightPrj * distanceToHeightPrj);

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

std::vector<Point> Ring::IntersectionWithFigure(Figure * otherFigure)
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

