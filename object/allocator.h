#pragma once




namespace duck {
namespace object {

template<typename T>
class Allocator
{
public:
    virtual T* allocate() = 0;
    virtual void deallocate(T* p) = 0;
};

}//namespace object
}//namespace duck








