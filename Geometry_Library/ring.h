#ifndef RING_HEADER
#define RING_HEADER

#include "additionals.h"
#include "figure.h"

class Ring : public Figure
{
private:
	Point center;
	double radius;
	std::string type;
	Equation CircleEq;
public:
	Ring(Point, double);	//center->radius
	Ring(double, double, double);
	Ring();

	double getSurface() const;
	double getPerimeter() const;

	bool containsPoint(Point) const;
	bool containsPoint(double, double) const;

	std::string getType() const;

	void rotate(double) ; // rotation is in radians
	Ring getInscribedCircle() const;
	Point getSurroundingRectangleSP() const; // returns the starting point of the rectangle(otherwise ring<->rectangle)

	void save(std::ostream &out);
    void load(std::istream &in);
	void print();

	Equation getEquation();
	void setEquation();

	std::vector<Point> IntersectionWithLines(std::vector<LineEquation>);
	std::vector<Point> IntersectionWithCircle(CircleEquation);
	std::vector<Point> IntersectionWithFigure(Figure*);
private:
	

};
#endif // !RING_HEADER
