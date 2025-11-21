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
    
    unique_ptr(unique_ptr&& other) noexcept : ptr(other.ptr) { other.ptr = nullptr; }

    T* get() const { return ptr; }

    T* release()
    {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void reset(T* new_ptr=nullptr)
    {
        delete ptr;
        ptr = new_ptr;
    }
};




int main()
{    

}

