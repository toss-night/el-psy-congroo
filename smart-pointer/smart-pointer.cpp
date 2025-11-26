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

template<typename T>
class shared_ptr
{
private:
    T* ptr;
    int* count;
    void addRef()
    {
        if (count)
        {
            (*count)++;
        }
    }
    void releaseRef()
    {
        if (count && --(*count) == 0)
        {
            delete ptr;
            delete count;
            ptr = nullptr;
            count = nullptr;
        }
    }

public:
    explicit shared_ptr(T* obj = nullptr) : ptr(obj), count(obj ? new int(1) : nullptr) {}

    shared_ptr(T* p, int* cnt) : ptr(p), count(cnt) 
    {
        if (count) 
        {
            (*count)++;  
        }
    }

    shared_ptr(const shared_ptr& other) :ptr(other.ptr), count(other.count) { addRef(); }
    shared_ptr& operator= (const shared_ptr& other)
    {
        if (this != &other)
        {
            releaseRef();
            ptr = other.ptr;
            count = other.count;
            addRef();
        }
        return *this;
    }

    int use_count() const { return count ? *count : 0; }

    ~shared_ptr() { releaseRef(); }

    T* get() const { return ptr; }
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    explicit operator bool() const { return ptr != nullptr; }

    template<typename U>
    friend class weak_ptr;
};

template<typename T>
class weak_ptr
{
private:
    T* ptr;
    int* count;

public:
    weak_ptr() :ptr(nullptr), count(nullptr) {}
    
    weak_ptr(const shared_ptr<T>& other) :ptr(other.ptr), count(other.count) {}

    weak_ptr(const weak_ptr& other) :ptr(other.ptr), count(other.count) {}

    weak_ptr(weak_ptr&& other) noexcept :ptr(other.ptr), count(other.count) 
    {
        other.ptr = nullptr;
        other.count = nullptr;
    } 
    
    weak_ptr& operator=(weak_ptr&& other) noexcept 
    {
        if (this != &other) 
        {
            ptr = other.ptr;
            count = other.count;
            other.ptr = nullptr;
            other.count = nullptr;
        }
        return *this;
    }
    
    bool expired() const { return !count || *count == 0; };
 
    shared_ptr<T> lock() const
    {
        if (count && *count > 0)
        {
            return shared_ptr<T>(ptr, count);
        }
        return shared_ptr<T>();
    }

    int use_count() const { return count ? *count : 0; }
        
    void reset() 
    {
        ptr = nullptr;
        count = nullptr;
    }
};

int main()
{    
    return 0;
}

