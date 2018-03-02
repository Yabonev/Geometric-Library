#ifndef SQUARE_HEADER
#define SQUARE_HEADER


#include "additionals.h"
#include "ring.h"
#include "rectangle.h"
#include "triangle.h"
//#include "figure.h"

class Square : public Figure
{
private:
	double sideLength;
	Point startingPoint;
	std::string type;
	Equation sidesLines;

public:
	Square(Point, double); // sp->sidelength
	Square(double, double, double);

	double getSideLength() const;
	double getSurface() const;
	double getPerimeter() const;

	bool containsPoint(Point) const; 
	bool containsPoint(double, double) const; //uses coordinates

	std::string getType() const; 
	Point getCentroid() const;

	void rotate(double); // rotation is in radians

	Ring getCircumscribedCircle() const;
	Ring getInscribedCircle() const;
	Rectangle getSurroundingRectangle() const;

	//Figure* create();
	void save(std::ostream &out);
	void load(std::istream &in);
	void print();

	void setEquation();
	Equation getEquation();

	std::vector<Point> IntersectionWithLines(std::vector<LineEquation>);
	std::vector<Point> IntersectionWithCircle(CircleEquation);
	std::vector<Point> IntersectionWithFigure(Figure*);
private:
	//static int dummy;
	//static int registerClass();

};

#endif // !SQUARE_HEADER
