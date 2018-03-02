#ifndef FIGURE_HEADER
#define FIGURE_HEADER
#include "additionals.h"

class Figure;

struct Pair
{
	std::string type;
	Figure* emptyFigure;

	Pair(std::string _type, Figure* figure) :type(_type), emptyFigure(figure) {}
};

class Figure
{
public:
	virtual double getSurface() const = 0;
	virtual double getPerimeter() const = 0;

	virtual bool containsPoint(Point) const = 0;
	virtual bool containsPoint(double, double) const  = 0;

	virtual std::string getType() const = 0;

	virtual void rotate(double) = 0;

	virtual void save(std::ostream &out);
	virtual void load(std::istream &in);
	virtual void print() = 0;

	virtual Equation getEquation() = 0;

	static void addFigureType(std::string type, Figure *figure);

	virtual std::vector<Point> IntersectionWithFigure(Figure*) = 0;
	virtual std::vector<Point> IntersectionWithLines(std::vector<LineEquation>) = 0;
	virtual std::vector<Point> IntersectionWithCircle(CircleEquation) = 0;
private:
	static std::vector<Pair> allFigureTypes;
};

std::ostream& operator << (std::ostream &, std::vector<Figure*>);
std::istream& operator >> (std::istream &, std::vector<Figure*>&);
#endif // !FIGURE_HEADER
