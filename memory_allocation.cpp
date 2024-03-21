#include <iostream>
#include <new> // 引入标准库中的placement new

using namespace std;

class  MyClass{
    int val;
    string name;
public:
    string get_name(){
        return name;
    }
    MyClass(){};
    ~MyClass(){};
};


void placement_new(){
    char* buffer = new char[sizeof(MyClass)];
    MyClass* myObject = new (buffer) MyClass();

    // 对于通过placement new创建的对象，你应该直接调用对象的析构函数来销毁它，而不是使用delete操作符。
    // 这是因为placement new只是在给定的内存地址上构造对象，并不负责分配和释放内存。内存的管理需要由程序员手动控制。
    myObject->~MyClass();
}



void std_allocator(){
    std::allocator<int> allocator;
    int* array = allocator.allocate(10);  // 分配内存
    allocator.deallocate(array, 10);      // 释放内存
}


void allocate_on_stack(){
    char buffer[10]; // 分配足够的内存来存储一个char对象
    std::cout << "在预分配的内存中构造对象" << std::endl;
    auto p = new (buffer) char('a'); // 使用placement new在buffer指向的内存中构造对象

    std::cout << "buffer地址 " << static_cast<void*>(buffer) << std::endl;
	std::cout << "p的值 " << p << std::endl; // p此时被当成了c风格字符串
    std::cout << "p的地址 " << static_cast<void*>(p) << std::endl; // 访问对象的地址
    // 注意：不需要使用delete来释放内存，因为内存是在栈上分配的. 这样就可以在栈上分配内存
}


void use_malloc(){
    int* array = (int*)malloc(10 * sizeof(int));
    free(array);

}

// calloc：与malloc类似，但是它会将分配的内存初始化为零。
void  use_calloc(){
    int* array = (int*)calloc(10, sizeof(int));
    free(array);

}


void use_realloc(){
    int* array = (int*)malloc(10 * sizeof(int));
    array = (int*)realloc(array, 20 * sizeof(int));
    free(array);

}


void use_aligned_alloc(){
    int* array = (int*)aligned_alloc(16, 10 * sizeof(int));
    free(array);
}



int main() {




    return 0;
}
