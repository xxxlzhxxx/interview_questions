#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <utility>  // For std::forward

template <typename T>
class MyVector {
private:
    T* data;
    size_t capacity;
    size_t size;

    void increaseCapacity(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = std::move(data[i]);
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    MyVector() : data(nullptr), capacity(1), size(0) {
        data = new T[capacity];
    }

    ~MyVector() {
        delete[] data;
    }



    void push_back(const T& value) {
        if (size == capacity) {
            increaseCapacity(capacity * 2);
        }
        data[size++] = value;
    }



	// 模板参数包
    template <typename... Args>
    void emplace_back(Args&&... args) {     //函数参数包
        if (size == capacity) {
            increaseCapacity(capacity * 2);
        }
        new(&data[size++]) T(std::forward<Args>(args)...);
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
    MyVector<std::pair<int, std::string>> vec;
    vec.emplace_back(1, "one");
    vec.emplace_back(2, "two");
    vec.emplace_back(3, "three");

    for (size_t i = 0; i < vec.getSize(); ++i) {
        std::cout << "(" << vec[i].first << ", " << vec[i].second << ") ";
    }
    std::cout << std::endl;

    return 0;
}
