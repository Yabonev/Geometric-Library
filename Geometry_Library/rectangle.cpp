#include "stdafx.h"
#include "rectangle.h"

Rectangle::Rectangle(Point sp, double _width, double _height) : startingPoint(sp),
																	width(_width),
																  height(_height),
															   type("Rectangle") {
																	setEquation();
																				 }


Rectangle::Rectangle(double x, double y, double width, double height)
{
	startingPoint.x = x;
	startingPoint.y = y;
	this->width = width;
	this->height = height;
	type = "Rectangle";
	setEquation();


}

double Rectangle::getWidth() const
{
	return width;
}

double Rectangle::getHeight() const
{
	return height;
}

double Rectangle::getSurface() const
{
	return width * height;
}

double Rectangle::getPerimeter() const
{
	return 2 * (width + height);
}

bool Rectangle::containsPoint(Point P) const
{
	Point A = startingPoint;
	Point B(A.x + getWidth(), A.y);
	Point C(A.x + getWidth(), A.y + getHeight());
	Point D(A.x, A.y + getHeight());
	Triangle t1(A, B, P);
	Triangle t2(B, C, P);
	Triangle t3(C, D, P);
	Triangle t4(D, A, P);

	return getSurface() == t1.getSurface() + t2.getSurface() + t3.getSurface() + t4.getSurface();
}

bool Rectangle::containsPoint(double _x, double _y) const
{
	Point P(_x, _y);
	Point A = startingPoint;
	Point B(A.x + getWidth(), A.y);
	Point C(A.x + getWidth(), A.y + getHeight());
	Point D(A.x, A.y + getHeight());
	Triangle t1(A, B, P);
	Triangle t2(B, C, P);
	Triangle t3(C, D, P);
	Triangle t4(D, A, P);

	return getSurface() == t1.getSurface() + t2.getSurface() + t3.getSurface() + t4.getSurface();
}

std::string Rectangle::getType() const
{
	return type;
}

Point Rectangle::getCentroid() const
{
	Point D(startingPoint.x + width, startingPoint.y + height);
	Point Centroid(((startingPoint.x + D.x) * 0.5), ((startingPoint.y + D.y) * 0.5));
	return Centroid;
}

void Rectangle::rotate(double radians)
{
	startingPoint.rotatePoint(radians);
	setEquation();

}

Ring Rectangle::getCircumscribedCircle() const
{
	Point D(startingPoint.x + width, startingPoint.y + height);
	Point centroid(((startingPoint.x + D.x) * 0.5), ((startingPoint.y + D.y) * 0.5));
	GeometricVector Radius(startingPoint, centroid);
	double rds = Radius.getLength();
	Ring circumscribedCircle(centroid, rds);
	return circumscribedCircle;
}

Ring Rectangle::getInscribedCircle() const
{
	Point D(startingPoint.x + width, startingPoint.y + height);
	Point centroid(((startingPoint.x + D.x) * 0.5), ((startingPoint.y + D.y) * 0.5));
	Point B((startingPoint.x + width * 0, 5), startingPoint.y);
	GeometricVector radius(B, centroid);
	double rds = radius.getLength();
	Ring inscribedCircle(centroid, rds);
	if (width == height)
	{
		return inscribedCircle;
	}
	else
	{
		Ring nonexistantInscribedCircle(centroid, 0);
		return nonexistantInscribedCircle;
	}
}

Rectangle Rectangle::getSurroundingRectangle() const
{
	Rectangle surrRectangle(startingPoint, width, height);
	return surrRectangle;
}

void Rectangle::save(std::ostream & out)
{
	out << "Rectangle " << startingPoint.x << " " << startingPoint.y << " " << width << " " << height << " " ;
}

void Rectangle::load(std::istream & in)
{
	in >> startingPoint.x >> startingPoint.y >> width >> height;
}
void Rectangle::print()
{
	std::cout << "Rectangle(" << startingPoint.x << ", " << startingPoint.y << ", " <<
				   getWidth() << ", " << getHeight() << ")" << std::endl;
}

Equation Rectangle::getEquation()
{
	return sidesLines;
}

void Rectangle::setEquation()
{
	Point A = startingPoint;
	Point B(A.x + getWidth(), A.y);
	Point C(A.x + getWidth(), A.y + getHeight());
	Point D(A.x, A.y + getHeight());
	sidesLines.LE.push_back(LineEquation(A, B));
	sidesLines.LE.push_back(LineEquation(B, C));
	sidesLines.LE.push_back(LineEquation(C, D));
	sidesLines.LE.push_back(LineEquation(D, A));
}
std::vector<Point> Rectangle::IntersectionWithLines(std::vector<LineEquation> linesVector)
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
std::vector<Point> Rectangle::IntersectionWithCircle(CircleEquation CE)
{
	std::vector<Point> intersectionPoints;
	double root1, root2;
	std::vector<LineEquation> LE = sidesLines.LE;
	for (int i = 0; i < 4; i++)
	{
		double a = ((LE[i].A / LE[i].B) * (LE[i].A / LE[i].B)) + 1;
		double b = ((-2 * LE[i].A * LE[i].C) / (LE[i].B * LE[i].B))
			- ((2 * LE[i].A * CE.y0) / LE[i].B) - 2 * CE.x0;
		double c = (CE.y0 * CE.y0) - (CE.r * CE.r) + (CE.x0 * CE.x0) - ((2 * CE.y0 * LE[i].C) / LE[i].B) +
			(LE[i].C * LE[i].C) / (LE[i].B * LE[i].B); 
		double discriminant = b * b - 4 * a * c;
		if (discriminant == 0)
		{
			root1 = -b / (2 * a);
			Point p(root1, (-LE[i].A * root1) / LE[i].B + LE[i].C / LE[i].B);
			intersectionPoints.push_back(p);
		}
		else if (discriminant > 0)
		{
			root1 = (-b + sqrt(discriminant)) / (2 * a);
			root2 = (-b - sqrt(discriminant)) / (2 * a);
			Point p(root1, (-LE[i].A * root1) / LE[i].B + LE[i].C / LE[i].B);
			Point q(root2, (-LE[i].A * root2) / LE[i].B + LE[i].C / LE[i].B);
			intersectionPoints.push_back(p);
			intersectionPoints.push_back(q);
		}
	}
	return intersectionPoints;
}

std::vector<Point> Rectangle::IntersectionWithFigure(Figure * otherFigure)
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

