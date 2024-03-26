#include <memory>
#include <iostream>

using namespace std;

class B;

class A {
public:
	//shared_ptr <B> ptr;
	weak_ptr <B> ptr;
	~A(){
		cout << "A destructed" << endl;
	}
};


class B {
public:
	shared_ptr <A> ptr;
	~B(){
		cout << "B destructed" << endl;
	}
};




int main(){
	// shared 创建对象，weak接管对象
	auto a = make_shared<A>();
	auto b = make_shared<B>();

	a->ptr = b;
	b->ptr = a;



	return 0;
}


