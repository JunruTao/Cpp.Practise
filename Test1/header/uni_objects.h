#ifndef UNI_OBJECTS_H
#define UNI_OBJECT_H

#include <vector>
#include <string>

class Object{
    public:
    //Constructor & Destructor area
    Object();
    ~Object();

    //virtual functions
    virtual void Translate(std::vector<double>){};
    
    //common object functions
    void SetName(std::string name) {_name = name;} //setter

    void PrintBasicInfo();//Printing object information
    std::string GetName() const{ return _name;} // getter ->name
    unsigned int GetObjectCount() const{ return _Obj_count;}//getter ->count

    protected:
    std::vector<double> _uniPos{0,0,0};
    std::string _name{"unnamed_oject"};
    unsigned int _obj_id;

    private:
    static unsigned int _Obj_count;

};



#endif