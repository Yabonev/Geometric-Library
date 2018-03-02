#ifndef RECTANGLE_HEADER
#define RECTANGLE_HEADER

#include "additionals.h"
#include "ring.h"
#include "triangle.h"
#include "figure.h"


class Rectangle: public Figure
{
private:
	double width;
	double height;
	Point startingPoint;
	std::string type;
	Equation sidesLines;
public:
	Rectangle(Point, double, double); //sp ->width ->height
	Rectangle(double, double, double, double);

	double getWidth() const;
	double getHeight() const;
	double getSurface() const;
	double getPerimeter() const;

	bool containsPoint(Point) const; 
	bool containsPoint(double, double) const; //uses coordinates

	std::string getType() const; 
	Point getCentroid() const;

	void rotate(double); // rotation is in radians
	Ring getCircumscribedCircle() const;
	Ring getInscribedCircle() const ; //exists only if width == height
	Rectangle getSurroundingRectangle() const;

	void save(std::ostream &out);
	void load(std::istream &in);
	void print();

	void setEquation();
	Equation getEquation();

	std::vector<Point> IntersectionWithLines(std::vector<LineEquation>);
	std::vector<Point> IntersectionWithCircle(CircleEquation);
	std::vector<Point> IntersectionWithFigure(Figure*);
private:
	

};
#endif // !RECTANGLE_HEADER
