#include <iostream>
#include <vector>
#include <functional>
typedef std::function<void (int&)> action;

void for_each(std::vector < int > &a, action func){
	for (size_t i = 0; i < a.size(); ++i){
		func(a[i]);
	}
}

void inc(int& a){
	++a;
}

int main(){
	std::vector<int> v;
	int value;
	while(std::cin >> value){
		v.push_back(value);
	}

	action add = inc;

	for_each(a, add);

	for (size_t i = 0; i < v.size(); ++i){
		std::cout << v[i];
	}
}