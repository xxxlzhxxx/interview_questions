#include <iostream>


using namespace std;


template <typename T>
int fun1(T arg){
	return arg;
}


// 以递归方式解包，一定要设置递归结束的出口。例如本例中，无形参、函数体为空的 vir_fun() 函数就是递归结束的出口。
// Base case
template <typename T>
T fun2(T first) {
    return first;
}

template <typename T, typename... Types>
T fun2(T first, Types... args){
	return first + fun2(args...);
}


// 非递归方式解包
template <typename T>
void dispaly(T t) {
    cout << t << endl;
}


template <typename... args>
void vir_fun(args... argv)
{
    //逗号表达式+初始化列表
    int arr[] = { (dispaly(argv),0)... };
}


int main(){
	cout << fun2(1, 2, 5, 0) << endl;
	return 0;
}