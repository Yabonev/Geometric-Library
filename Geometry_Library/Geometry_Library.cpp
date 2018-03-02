// Geometry_Library.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "additionals.h"
#include "figure.h"
#include "circle.h"
#include "ring.h"
#include "square.h"
#include "rectangle.h"
#include "triangle.h"
#include "picture.h"

void test()
{
	std::vector<Figure*> figures;
	std::vector<Figure*> figaroo;
	figures.push_back(new Ring(1, 1, 3));
	figures.push_back(new Square(3, 3, 3));
	figures.push_back(new Rectangle(1, 1, 3, 3));
	figures.push_back(new Ring(2, 1, 3));
	figures.push_back(new Triangle(1, 1, 3, 3, 5, 5));
	figures.push_back(new Circle(1, 5, 3)); // 
	std::ofstream out;
	out.open("input.txt");
	out << figures;
	out.close();
	std::ifstream in;
	in.open("input.txt");
	in >> figaroo;
	for (size_t i = 0; i < 6; i++)
		std::cout << figaroo[i]->getType();
	std::cout << std::endl;

}
void pictureIntersectionTest()
{
	Picture picture, picture2;
	picture.addFigure(new Square(0, 0, 3));
	picture2.addFigure(new Square(1, 1, 3));
	picture2.addFigure(new Square(2, 2, 3));
	picture.intersectionPoints(picture2.getPicture());
	std::cout << std::endl;
	picture2.removeFigure(1);
	picture.intersectionPoints(picture2.getPicture());
}
int main()
{
	//test();
	//pictureIntersectionTest();
	system("pause");

	return 0;
}

