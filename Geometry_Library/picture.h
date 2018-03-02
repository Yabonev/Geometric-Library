#ifndef PICTURE_HEADER
#define PICTURE_HEADER

#include "additionals.h"
#include "square.h"
#include "rectangle.h"
#include "triangle.h"
#include "ring.h"
#include "circle.h"
#include "figure.h"


class Picture
{
private:
	std::vector<Figure*> picture;
public:
	std::vector<Figure*> getPicture();
	void addFigure(Figure*);
	void removeFigure(int);
	void printElements();
	std::vector<Point> intersectionPoints(std::vector<Figure*> otherPicture);
};
#endif // !PICTURE_HEADER
