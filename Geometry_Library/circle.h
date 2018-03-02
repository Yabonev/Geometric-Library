#ifndef CIRCLE_HEADER
#define CIRCLE_HEADER

#include "additionals.h"
#include "ring.h"
#include "rectangle.h"
#include "figure.h"

class Circle : public Figure
{
private:
	Point center;
	double radius;
	std::string type;
	Equation CircleEq;

public:
	Circle(Point, double); //center->radius
	Circle(double, double, double);

	unsigned int numberOfCirclesContained(Circle) const; 

	double getSurface() const;
	double getPerimeter() const;

	bool containsPoint(Point) const;
	bool containsPoint(double, double) const;

	std::string getType() const; 

	void rotate(double); // rotation is in radians

	Ring getInscribedCircle() const;
	Rectangle getSurroundingRectangle() const;

	void save(std::ostream &out);
	void load(std::istream &in);
	void print();

	void setEquation();
	Equation getEquation();

	std::vector<Point> IntersectionWithLines(std::vector<LineEquation>);
	std::vector<Point> IntersectionWithCircle(CircleEquation);
	std::vector<Point> IntersectionWithFigure(Figure*);	
};
#endif // !CIRCLE_HEADER
