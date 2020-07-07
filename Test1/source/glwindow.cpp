#include <iostream>
#include <uni_objects.h>
#include <point_obj.h>
#include <memory>
#include <vector>

int main()
{
	std::cout << "intialization \n ........ " << std::endl;

	
	//[1] Storing Data on Heap, using unique pointers
	std::vector<std::unique_ptr<Object>> objectList;

	//[2] Using Move Semantics, create objects
	for (int i = 0; i < 6; ++i)
	{
		objectList.emplace_back(std::make_unique<Object>());
		objectList[i]->SetName("Object" + std::to_string(i));
	}


	//[3] Printing Object info
	for (auto& e : objectList) {e->PrintBasicInfo();}
	


	//Allow all internal operations to print instructions
	Point::Toggle_PrintAllOperation();
	Point::Toggle_PrintAllOperation();

	//create points from XYZ
	Point a(3, 5, 4);
	Point b(4, 6, 9);

	//using 'Distance to' function & setter functions
	b.Z(3 + a.DistanceTo(b));
	a.X(b.Y());
	b.SetXYZ(a.X(), 3.4f, 7.08f);

	b.Translate(a); //treating a as a vector;
	a.Translate(2.3f, 1);//Translate along Y axis 2.3 units

	//basic operator +- and copy value
	b.PrintPosToConcole();
	a.PrintPosToConcole();
	Point c = (a - b + b);

	//printing point results
	a.PrintPosToConcole();
	b.PrintPosToConcole();
	c.PrintPosToConcole();


	return 0;
}