#include <iostream>
#include <uni_objects.h>
#include <memory>
#include <vector>

int main()
{
    std::cout << "intialization \n ........ " << std::endl;
    //remove the old-way init;
    //Object obj1, obj2, obj3, obj4;
    //obj1.SetName("Empty Object");
    std::vector<std::unique_ptr<Object>> objectList;
    
    for (int i = 0; i < 6; ++i) 
    {
        objectList.emplace_back(std::make_unique<Object>());
        objectList[i]->SetName("Object" + std::to_string(i));
    }
    
    for (auto& e : objectList) 
    {
        e->PrintBasicInfo();
    }

    return 0;
}