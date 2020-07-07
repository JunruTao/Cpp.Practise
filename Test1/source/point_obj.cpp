#include <point_obj.h>
#include <stdio.h>
#include <string>
#include <cmath>

Point::Point()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
	Point::Op_PrintMessage("NEW POINT - 0,0,0");
}

Point::Point(const Point& point)
{
	Point::Op_PrintMessage("Copy Position - construct");
	_x = point._x;
	_y = point._y;
	_z = point._z;
}

Point& Point::operator=(const Point& point)
{
	Point::Op_PrintMessage("Copy Position - assignment");
	_x = point._x;
	_y = point._y;
	_z = point._z;
	return *this;
}

//*******[Operators]******
Point Point::operator+(const Point point)
{
	Point::Op_PrintMessage("Adding Positions");
	return Point(_x + point._x, _y + point._y, _z + point._z);
}

Point Point::operator-(const Point point)
{
	Point::Op_PrintMessage("Subtract Positions");
	return Point(_x - point._x, _y - point._y, _z - point._z);
}

//*******[Major Tool Functions]*******
void Point::Translate(const Point point)
{
	Point::Op_PrintMessage("Translate Point");
	_x += point._x;
	_y += point._y;
	_z += point._z;
}

void Point::Translate(double value, int axis)
{
	switch (axis)
	{
	default: printf("#.#.#.# invalid_axis #.#.#.#");
		break;
	case 0: _x += value;
		Point::Op_PrintMessage("Translate along X <- " + std::to_string(value));
		break;
	case 1: _y += value;
		Point::Op_PrintMessage("Translate along Y <- " + std::to_string(value));
		break;
	case 2: _z += value;
		Point::Op_PrintMessage("Translate along Z <- " + std::to_string(value));
		break;
	}
}
double Point::DistanceTo(const Point point) const
{
	double dist;
	dist = std::sqrt(
		std::pow(point._x - _x, 2) +
		std::pow(point._y - _y, 2) +
		std::pow(point._z - _z, 2));
	Point::Op_PrintMessage("returning 2 point distance |a->b| = " + std::to_string(dist));
	return dist;
}

//*******[Utilities]*******
void Point::Op_PrintMessage(std::string m)
{
	if (_IF_PRINT_OPERATOR_MES) {
		printf("--- Points Operation : [ %s ]\n", m.c_str());
	}
}

void Point::PrintPosToConcole()
{
	printf("--------------[Point]at:[%p]-----------------\n");
	printf("Position.[X:%f]\nPosition.[Y:%f]\nPosition.[Z:%f]\n"
		, _x, _y, _z);
	printf("###\n");
}

bool Point::_IF_PRINT_OPERATOR_MES = false;

void Point::Toggle_PrintAllOperation() {
	_IF_PRINT_OPERATOR_MES = !_IF_PRINT_OPERATOR_MES;
	if (_IF_PRINT_OPERATOR_MES) {
		printf("...[toggle = ON]...\nwill be Printing all points' detail operations\n.\n");
	}
	else
	{
		printf("...[toggle = OFF]...\npoints' detail operations are now hidden\n.\n");
	}
}