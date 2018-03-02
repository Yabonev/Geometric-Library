#include "stdafx.h"
#include "figure.h"
#include <assert.h>
#include "factory.h"

std::vector<Pair> Figure::allFigureTypes;

std::ostream & operator<<(std::ostream & out, std::vector<Figure*> figures)
{	
	size_t vectorSize = figures.size();
	out << vectorSize << " ";
	for (size_t size = 0; size < vectorSize; size++)
	{
		figures[size]->save(out);
	}
	return out;
}

std::istream & operator>>(std::istream &in, std::vector<Figure*>& figures)
{
	size_t vectorSize;
	in >> vectorSize;
	std::string type;
	for (size_t size = 0; size < vectorSize; size++)
	{
		in >> type;
		Figure * newFigure = Factory::factory(type);
		newFigure->load(in);
		figures.push_back(newFigure);
	}
	return in;
}

void Figure::save(std::ostream & out)
{
}

void Figure::load(std::istream & in)
{
}





void Figure::addFigureType(std::string type, Figure * figure)
{
	allFigureTypes.push_back(Pair(type, figure));
}
