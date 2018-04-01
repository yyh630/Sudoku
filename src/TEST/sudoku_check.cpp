#include <iostream>
#include "sudoku_basic.h"

using namespace std;

bool runApplication() {
	char s[SUDOKU_SIZE][SUDOKU_SIZE];
	if (read_sudoku(s) == false) return false;
	// print_sudoku(s);
	if (check_sudoku(s) == false) return false;
	return true;
}

int main() {
	bool valid = runApplication();
	if (valid) cout << "true" << endl;
	else cout << "false" << endl;
	return 0;	
}

