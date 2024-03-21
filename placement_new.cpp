#include <iostream>
#include <new> // 引入标准库中的placement new

int main() {
    char buffer[10]; // 分配足够的内存来存储一个char对象
    std::cout << "在预分配的内存中构造对象" << std::endl;
    auto p = new (buffer) char('a'); // 使用placement new在buffer指向的内存中构造对象

    std::cout << "buffer地址 " << static_cast<void*>(buffer) << std::endl;

	std::cout << "p的值 " << p << std::endl; // p此时被当成了c风格字符串
    std::cout << "p的地址 " << static_cast<void*>(p) << std::endl; // 访问对象的地址

    // 注意：不需要使用delete来释放内存，因为内存是在栈上分配的
    return 0;
}
