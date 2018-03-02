#include "stdafx.h"
#include "picture.h"

std::vector<Figure*> Picture::getPicture()
{
	return picture;
}

void Picture::addFigure(Figure * givenFigure)
{
	picture.push_back(givenFigure);
}

void Picture::removeFigure(int index)
{	
	std::vector<Figure*>::iterator it;
	int i = 0;
	for (it = picture.begin(); it < picture.end(); it++,i++)
	{
			if(i == index)
			{
				picture.erase(it);
				return;
			}
	}	
}

void Picture::printElements()
{
	for (unsigned int i = 0; i < picture.size(); i++)
	{
		picture[i]->print();
	}
}

std::vector<Point> Picture::intersectionPoints(std::vector<Figure*> otherPicture)
{	
	std::vector<Point> IntersectionPoints;
	std::vector<Point> dummyVector;
	std::vector<Point>::iterator it;
	for (unsigned int i = 0; i < picture.size(); i++)
	{
		for (unsigned int j = 0; j < otherPicture.size(); j++)
		{
			dummyVector = picture[i]->IntersectionWithFigure(otherPicture[j]);
			for (unsigned int counter = 0; counter < dummyVector.size(); counter++)
			{
				IntersectionPoints.push_back(dummyVector[counter]);
			}
		}
	}	
	
	Point zombiePoint1(42.42, 42.42), zombiePoint2(-42.42, -42.42);
	
	for (unsigned int i = 0; i  < IntersectionPoints.size() - 1; i++)
	{
		for (unsigned int j = i + 1; j < IntersectionPoints.size(); j++) // най-голямата кръпка в
																		 // историята на програмирането
		{
			if (IntersectionPoints[i] == IntersectionPoints[j])
				it = IntersectionPoints.erase(IntersectionPoints.begin() + j);
			if (IntersectionPoints[0] == zombiePoint1 ||
				IntersectionPoints[0] == zombiePoint2) 
				it = IntersectionPoints.erase(IntersectionPoints.begin());
			if (IntersectionPoints[j] == zombiePoint1 ||
				IntersectionPoints[j] == zombiePoint2)
				it = IntersectionPoints.erase(IntersectionPoints.begin() + j);
		}
	}

	for (unsigned int i = 0; i < IntersectionPoints.size(); i++)
	{
		IntersectionPoints[i].print();
	}
	return IntersectionPoints;
}
