#include <iostream>

int main(int argc, char** argv){
	using namespace std;
	int calc[21];
	calc[0] = 0;
	calc[1] = 1;
	int N;
	cin >> N;
	for(int i = 2; i < 21; i++){
		calc[i] = calc[i - 2] + calc [i - 1];
	}

	cout << calc[N] << endl;
}