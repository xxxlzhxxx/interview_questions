#include <iostream>

template <typename T>
class UniquePtr {
private:
    T* ptr;

public:
    // 构造函数, explict关键字：显示构造函数，不能隐式转换
    // noexcept告诉编译器函数不会发生异常，有利于编译器做优化
    explicit UniquePtr(T* p = nullptr) noexcept: ptr(std::move(p)) {}

    // 默认构造, constexpr说明产生constexpr对象, 所有成员都是编译期可求值
    constexpr UniquePtr() noexcept: ptr(nullptr){}

    // 析构函数
    ~UniquePtr() {
        delete ptr;
    }

    // 移动构造函数
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
        // other.swap(*this); // 此函数也可以这么写
    }

    // 移动赋值运算符
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        // other.swap(*this); // 上方if也可以用此行代替
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

    // 重置指针, 删除老的, 指向新的
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = nullptr;
        std::swap(ptr, p);
    }

    // 交换资源
    void swap(UniquePtr& other) {
        std::swap(ptr, other.ptr);
    }

    // 重载bool运算符
    explicit operator bool() const noexcept {
        return ptr;
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
