#include <uni_objects.h>

unsigned int Object::_Obj_count = 0;

//define object constructor #1
Object::Object()
{
    _Obj_count ++;
    _obj_id = _Obj_count;
}

//define object destructor 
Object::~Object()
{
    _Obj_count --;
}