#include <iostream>

template <typename T>
class UniquePtr {
private:
    T* ptr;

public:
    // 构造函数, explict关键字：显示构造函数，不能隐式转换
    explicit UniquePtr(T* p = nullptr) : ptr(p) {}

    // 析构函数
    ~UniquePtr() {
        delete ptr;
    }

    // 移动构造函数
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // 移动赋值运算符
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // 删除拷贝构造函数和拷贝赋值运算符
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // 重载解引用运算符
    T& operator*() const {
        return *ptr;
    }

    // 重载箭头运算符
    T* operator->() const {
        return ptr;
    }

    // 获取原始指针
    T* get() const {
        return ptr;
    }

    // 释放所有权
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // 重置指针
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};

int main() {
    UniquePtr<int> p1(new int(10));
    std::cout << *p1 << std::endl; // 输出: 10

    UniquePtr<int> p2 = std::move(p1);
    std::cout << *p2 << std::endl; // 输出: 10

    p1.reset(new int(20));
    std::cout << (p1 ? *p1 : 0) << std::endl; // 输出: 20

    p2.reset();
    std::cout << (p2 ? *p2 : 0) << std::endl; // 输出: 0

    return 0;
}
