#include <iostream>

int main(int argc, char** argv){
	using namespace std;
	int n;
	int m;
	cin >> n >> m;
	int *matrix = new int[n * m];
	int** ptrs = new int*[n];

	for(int i = 0; i < n; i++){
		ptrs[i] = &matrix[i * n];
	}
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; j++)
			ptrs[i][j] = i * j;
	}

	cout << ptrs[1][3] << endl;
	delete[] matrix;
	delete[] ptrs;
}