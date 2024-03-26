#include <iostream>

using namespace std;


void process(int& i){
	cout << i << " lvalue" << endl;
}

void process(int&& i){
	cout << i << " rvalue" << endl;
}

template <typename T>
void bad_forward(T&& i){ // 万能引用
	process(i);
}

// 引用折叠，左值int && & == int &； 右值 int = int && 


template <typename T>
void perfect_forward(T&& i){ // 万能引用 universal template
	process(static_cast<T&&>(i));
}

//  封装起来，这就是实际的forward
template <typename T>
T&& myForward(typename std::remove_reference<T>::type& arg) {
    return static_cast<T&&>(arg);
}








int main(){

	int i = 1;
	// all left val
	bad_forward(i);
	bad_forward(1);



	perfect_forward(i);
	perfect_forward(1);



	return 0;
}







