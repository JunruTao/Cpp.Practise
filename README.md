# C++ General Tests
Learning c++ and practice
> current learning subject:
* `OOP and Inheritance`
* `manipulating virtual functions`
* `smart pointers`
* `multi-threading`

#####7/8/2020 Update:
Having issues using pthread using MinGW libraries, however the thread functions in Visual Studio is working just fine. New Project is appended down to pratices some threading techniques using modern C++ 11 or higher functions. So more updates will be focused on:
* `std::future`
* `std::promise`
* `std::async`'s thread pool features to start tasks
* `std::mutax` `std::lock()`- `lock_guard<>`, `unique_lock<>`

---
:notebook:
**For compiling using cmake and MinGW, make sure using the [mingw-threads solution(repo here)](https://github.com/meganz/mingw-std-threads)**

:notebook:
**Polymorphism:** the base class must have a `virtual destructor` hence the child-class `destructor` will be triggered.

:notebook:
**Static Functions** must be defined in the header files if not in the `main.cpp`
