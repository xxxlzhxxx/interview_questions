

template <typename T>
class unique_pointer{

	T* ptr;

public:
	unique_pointer(T* p): ptr(p){

	}

	unique_pointer(const unique_pointer&) = delete;
	unique_pointer& operator=(const unique_pointer&) = delete;







};