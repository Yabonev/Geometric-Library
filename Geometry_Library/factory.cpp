#include "stdafx.h"
#include "factory.h"

Figure * Factory::factory(std::string type)
{
	if (type == "Square")
	{
		return new Square(0, 0, 0);
	}
	else if(type == "Rectangle")
	{
		return new Rectangle(0, 0, 0, 0);
	}
	else if (type == "Triangle")
	{
		return new Triangle(0, 0, 0, 0, 0, 0);
	}
	else if (type == "Ring")
	{
		return new Ring(0, 0, 0);
	}
	else if(type == "Circle")
	{
		return new Circle(0, 0, 0);
	}

}
