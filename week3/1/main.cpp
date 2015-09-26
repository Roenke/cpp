#include <iostream>

int f(){
	using namespace std;
	int *a[4] = {};
	std::cout << "Stack. Current = " << a  << endl;
	return 0;
}

int main(){
	using namespace std;
	int* a = new int[2]();
	std::cout << "Heap. Current = " << &(a[0]) << " Next = " << &(a[1]) << endl;
	f();
	f();
}