#ifndef FACTORY_HEADER
#define FACTORY_HEADER

#include "additionals.h"
#include "figure.h"
#include "circle.h"
#include "ring.h"
#include "square.h"
#include "rectangle.h"
#include "triangle.h"

class Factory
{
public:
	static Figure* factory(std::string);
};
#endif // !FACTORY_HEADER
