#include <uni_objects.h>

#include <iostream>

//***initialise static number outside of header file:
unsigned int Object::_Obj_count = 0;

//define object constructor #1
Object::Object()
{
    _Obj_count ++;
    _obj_id = _Obj_count;

    std::cout << "creating object.. at: [" << this << "] and global has " 
        << _Obj_count << "objects.\n";
}

//define object destructor 
Object::~Object()
{
    _Obj_count --;
    if (_Obj_count == 0)
    {
        std::cout << "[Destroy all Instance of Objects]\n";
    }
}

//Object Printing info here;
void Object::PrintBasicInfo() 
{
    std::cout << "[Printing Object Info] -- Object ID: " << _obj_id << std::endl;
    std::cout << "--------------------------     NAME: " << _name << std::endl;

}