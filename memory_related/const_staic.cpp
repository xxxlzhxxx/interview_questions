#include <iostream>
using namespace std;



// 静态局部变量：当static用于函数内的局部变量时，该变量的生命周期将延伸到整个程序的运行期间，
// 但它的作用域仍然局限于该函数内。这意味着即使函数执行结束，该变量的值也会保持不变，并在下次函数调用时保留上次的值。
// in data segement
void func() {
    static int counter = 0;
    counter++;
    std::cout << counter << std::endl;
}

// 静态全局变量：当static用于全局变量时，它将该变量的作用域限制在声明它的文件内，其他文件不能直接访问该变量。
// 这有助于避免全局变量之间的命名冲突。
// in data segement
static int globalVar = 10;



class MyClass {
public:
	// 静态成员变量：在类中，static用于声明静态成员变量，
	// 这意味着该变量被该类的所有对象共享。静态成员变量在类外部初始化，并且不依赖于任何特定对象的存在。
	// data segement
    static int staticVar;


	//静态成员函数：在类中，static也可以用于声明静态成员函数。
	//静态成员函数不能访问类的非静态成员变量和非静态成员函数，因为它们不依赖于任何特定对象的存在。它们通过类名而不是对象来调用。
	// code segement
    static void staticFunc() {
        std::cout << "Static function called" << std::endl;
    }	
};

int MyClass::staticVar = 0;









