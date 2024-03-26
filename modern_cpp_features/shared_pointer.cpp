#include <iostream>
#include <atomic>

template <typename T>
class SharedPtr {
private:
    T* ptr;
    std::atomic<int>* count;
    // 释放资源
    void release() {
        if (count && --(*count) == 0) {
            delete ptr;
            delete count;
            ptr = nullptr;
            count = nullptr;
        }
    }

public:
    // 构造函数
    explicit SharedPtr(T* p = nullptr) : ptr(p), count(new std::atomic<int>(1)) {}

    // 拷贝构造函数
    SharedPtr(const SharedPtr& other) : ptr(other.ptr), count(other.count) {
        ++(*count);
    }

    // 移动构造函数
    SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), count(other.count) {
        other.ptr = nullptr;
        other.count = nullptr;
    }

    // 析构函数
    ~SharedPtr() {
        release();
    }

    // 拷贝赋值运算符
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            count = other.count;
            ++(*count);
        }
        return *this;
    }

    // 移动赋值运算符
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            count = other.count;
            other.ptr = nullptr;
            other.count = nullptr;
        }
        return *this;
    }

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

    // 获取引用计数
    int use_count() const {
        return count ? *count : 0;
    }


};

int main() {
    SharedPtr<int> p1(new int(10));
    std::cout << "p1 use_count: " << p1.use_count() << std::endl; // 输出: 1

    SharedPtr<int> p2 = p1;
    std::cout << "p1 use_count: " << p1.use_count() << std::endl; // 输出: 2
    std::cout << "p2 use_count: " << p2.use_count() << std::endl; // 输出: 2

    SharedPtr<int> p3(std::move(p2));
    std::cout << "p2 use_count: " << p2.use_count() << std::endl; // 输出: 0
    std::cout << "p3 use_count: " << p3.use_count() << std::endl; // 输出: 2

    return 0;
}
