#ifndef TRIANGLE_HEADER
#define TRIANGLE_HEADER

#include "additionals.h"
#include "ring.h"
//#include "figure.h"

class Triangle : public Figure
{
private:
	Point A;
	Point B;
	Point C;
	std::string type;
	Equation sidesLines;
public:
	Triangle(Point, Point, Point); //not rearranged points
	Triangle(double, double, double, double, double, double);

	double getAngleBetweenSides(Point, Point) const; // exclude the point where the angle is
	double getSurface() const;
	double getPerimeter() const;

	bool containsPoint(Point) const;
	bool containsPoint(double, double) const;

	std::string getType() const; 
	Point getCentroid() const;

	void rotate(double); // rotation is in radians
	Ring getCircumscribedCircle() const;
	Ring getInscribedCircle()const;
	Point getSurroundingRectangleSP() const; // triangle<->rectangle problem
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
#endif // !TRIANGLE_HEADER
