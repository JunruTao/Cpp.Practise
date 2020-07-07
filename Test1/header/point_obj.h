#ifndef POINT_OBJ_H
#define POINT_OBJ_H

#include <string>

class Point
{
private:
	double _x;
	double _y;
	double _z;

	//[Utility Varibles]
	static bool _IF_PRINT_OPERATOR_MES;
	//[Iternal Functions]
	static void Op_PrintMessage(std::string m);

public:
	//*******[Constructors]*******
	Point();
	Point(double x, double y, double z) :_x(x), _y(y), _z(z) { Op_PrintMessage("NEW POINT from X,Y,Z"); };

	//*******[copy construcror]******
	Point(const Point& point);
	Point& operator=(const Point& point);

	//*******[Operators]******
	Point operator+(const Point point);
	Point operator-(const Point point);

	//*********[Setters/Getters]*********
	void SetXYZ(double x, double y, double z) { _x = x;_y = y;_z = z; Op_PrintMessage("Set new X,Y,Z"); }
	void X(double x) { _x = x; Op_PrintMessage("Set new X"); }
	void Y(double y) { _y = y; Op_PrintMessage("Set new Y"); }
	void Z(double z) { _z = z; Op_PrintMessage("Set new Z"); }
	double X() const { return _x; }
	double Y() const { return _y; }
	double Z() const { return _z; }

	//*******[Major Tool Functions]*******

	void Translate(const Point point);
	void Translate(double value, int axis);
	double DistanceTo(const Point point)const;


	//*******[Utilities]*******
	void PrintPosToConcole();
	static void Toggle_PrintAllOperation();
};




#endif