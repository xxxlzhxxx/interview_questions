#include <iostream>


using namespace std;



class A {
	int val;
	string name;

public:
	A(int v, string n): val(v), name(n){
		cout << "A is constructed" << endl;
	}
	~A(){};

	string get_name(){
		return name;
	}

};




int main(){
	A a = {10, "qwer"};



	return 0;
}