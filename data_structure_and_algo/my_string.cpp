#include <iostream>
#include <cstring>


class String {
private:
    char* data;
    size_t length;

public:
    // 构造函数
    String(const char* str = "") {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }

    // 拷贝构造函数
    String(const String& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }

    // 赋值运算符
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    // 析构函数
    ~String() {
        delete[] data;
    }

    // 获取字符串长度
    size_t size() const {
        return length;
    }

    // 获取C风格字符串
    const char* c_str() const {
        return data;
    }
};



