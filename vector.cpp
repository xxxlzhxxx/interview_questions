#include <iostream>
#include <memory> // for std::allocator
#include <algorithm> // for std::reverse
#include <stdexcept> // for std::out_of_range

template <typename T>
class MyVector {
private:
    std::allocator<T> alloc; // 使用std::allocator来分配内存
    T* data;
    size_t capacity;
    size_t size;

    void increaseCapacity(size_t newCapacity) {
        T* newData = alloc.allocate(newCapacity); // 使用alloc分配内存
        for (size_t i = 0; i < size; ++i) {
            alloc.construct(newData + i, std::move(data[i])); // 使用alloc构造对象
            alloc.destroy(data + i); // 使用alloc销毁对象
        }
        alloc.deallocate(data, capacity); // 使用alloc释放内存
        data = newData;
        capacity = newCapacity;
    }

public:
    MyVector() : data(nullptr), capacity(1), size(0) {
        data = alloc.allocate(capacity); // 使用alloc分配内存
    }

    ~MyVector() {
        for (size_t i = 0; i < size; ++i) {
            alloc.destroy(data + i); // 使用alloc销毁对象
        }
        alloc.deallocate(data, capacity); // 使用alloc释放内存
    }

    void push_back(const T& value) {
        if (size == capacity) {
            increaseCapacity(capacity * 2);
        }
        alloc.construct(data + size, value); // 使用alloc构造对象
        ++size;
    }

    template <typename... Args>
    void emplace_back(Args&&... args) {
        if (size == capacity) {
            increaseCapacity(capacity * 2);
        }
        alloc.construct(data + size, std::forward<Args>(args)...); // 使用alloc构造对象
        ++size;
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void resize(size_t newSize) {
        if (newSize > capacity) {
            increaseCapacity(newSize);
        }
        size = newSize;
    }

    void reverse() {
        std::reverse(data, data + size);
    }

    void shrink_to_fit() {
        if (size < capacity) {
            increaseCapacity(size);
        }
    }

    void reserve(size_t newCapacity) {
        if (newCapacity > capacity) {
            increaseCapacity(newCapacity);
        }
    }
};

int main() {
    MyVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.emplace_back(3);

    for (size_t i = 0; i < vec.getSize(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
