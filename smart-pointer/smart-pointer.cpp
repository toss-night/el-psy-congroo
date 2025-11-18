#include <iostream>



template<typename T>
class unique_ptr
{
private:
    T* ptr;

public:    
    explicit unique_ptr(T* obj=nullptr) :ptr(obj) {}
    ~unique_ptr() { delete ptr; }
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator = (const unique_ptr&) = delete;
    
};




int main()
{
    
}

