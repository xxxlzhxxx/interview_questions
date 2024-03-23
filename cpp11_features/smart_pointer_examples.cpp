#include <iostream>
#include <memory>
#include <vector>

using namespace std;

void test_reference_counting_in_function_v(shared_ptr<int> ptr){
	cout << "-------test_reference_counting_in_function, pass by value---------" << endl;
	cout << "ptr1: reference counting: " << ptr.use_count() << endl;
	auto ptr_tmp = ptr;
	cout << "ptr1: reference counting: " << ptr.use_count() << endl;
}

void test_reference_counting_in_function_r(shared_ptr<int>& ptr){
	cout << "-------test_reference_counting_in_function, pass by reference---------" << endl;
	cout << "ptr1: reference counting: " << ptr.use_count() << endl;
	auto ptr_tmp = ptr;
	cout << "ptr1: reference counting: " << ptr.use_count() << endl;
}

vector <int> v;

int main(){
	auto shared_p1 = make_shared<int>(10);
	cout << "reference couting: " << shared_p1.use_count() << endl;
	auto shared_p2 = shared_p1;
	cout << "reference couting: " << shared_p2.use_count() << endl;
	auto raw_pointer = shared_p1.get();
	cout << "address: " << raw_pointer << endl;
	cout << "size of raw pointer: " << sizeof(raw_pointer) << ", size of shared_ptr: " << sizeof(shared_p1) << endl;


	// pass shared ptr to func
	test_reference_counting_in_function_v(shared_p1);
	cout << "reference couting: " << shared_p2.use_count() << endl;

	test_reference_counting_in_function_r(shared_p1);
	cout << "reference couting: " << shared_p2.use_count() << endl;


	// make shared does not support array
	// auto shared_p3 = make_shared<int[]>(int[10]);    error
	auto shared_p3 = shared_ptr<int[]>(new int[10], default_delete<int[]>());













	return 0;
}