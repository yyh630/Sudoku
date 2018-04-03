#include "sudoku_basic.h"
#include <set>
#include <iostream>
using namespace std;

bool check_duplicate(char arr[SUDOKU_SIZE]) {
	set<char> s;
	for(int i = 0;i < SUDOKU_SIZE; i++) {
		char n = arr[i];
		if (n == '0') continue;
		if(s.count(n) > 0) return false;
		s.insert(n);
	}
	return true;
}

bool check_rows(char sudoku[SUDOKU_SIZE][SUDOKU_SIZE]) {
	for(int r = 0; r< SUDOKU_SIZE; r++) {
		if(check_duplicate(sudoku[r]) == false) 
			return false;
	}	
	return true;
}

bool check_cols(char sudoku[SUDOKU_SIZE][SUDOKU_SIZE]) {
	for(int c = 0; c< SUDOKU_SIZE; c++) {
		char arr[SUDOKU_SIZE];
		for(int r = 0; r < SUDOKU_SIZE; r ++) {
			arr[r] = sudoku[r][c];
		}
		if(check_duplicate(arr) == false) 
			return false;
	}	
	return true;
}


bool check_box(char sudoku[SUDOKU_SIZE][SUDOKU_SIZE], int i, int j) {
	int start_r = i * SUDOKU_BOX_SIZE;
	int start_c = j * SUDOKU_BOX_SIZE;
	char arr[SUDOKU_SIZE];
	int n = 0;

	for(int dr = 0; dr < SUDOKU_BOX_SIZE; dr ++ ) {
		for(int dc = 0; dc < SUDOKU_BOX_SIZE; dc ++) {
			int r = start_r + dr;
			int c = start_c + dc;
			arr[n++] = sudoku[r][c];
		}
	}
	if(check_duplicate(arr) == false) {
		return false;
	}
	return true;
}

bool check_boxes(char sudoku[SUDOKU_SIZE][SUDOKU_SIZE]) {
	for (int r = 0; r < SUDOKU_BOX_SIZE; r ++ ) {
		for (int c= 0; c < SUDOKU_BOX_SIZE; c ++ ) {
			if(check_box(sudoku, r, c) == false ) {
				return false;
			}	
		}
	}
	return true;
}

bool check_diag(char sudoku[SUDOKU_SIZE][SUDOKU_SIZE]) {
	char arrPos[SUDOKU_SIZE];
	char arrNeg[SUDOKU_SIZE];
	int n = 0;

	for (int r = 0; r < SUDOKU_SIZE; r ++ ) {
		arrPos[n] = sudoku[r][r];
		arrNeg[n++] = sudoku[r][SUDOKU_SIZE - r];
	}

	if(check_duplicate(arrPos) == false || check_duplicate(arrNeg) == false) {
		return false;
	}
	return true;
}

// const int SUDOKU_SIZE = 9;
bool check_sudoku(char sudoku[SUDOKU_SIZE][SUDOKU_SIZE]) {
	if(check_rows(sudoku) == false) return false;
	if(check_cols(sudoku) == false) return false;
	if(check_boxes(sudoku) == false) return false;
	return true;
}

bool check_diag_sudoku(char sudoku[SUDOKU_SIZE][SUDOKU_SIZE]){	
	if(check_rows(sudoku) == false) return false;
	if(check_cols(sudoku) == false) return false;
	if(check_boxes(sudoku) == false) return false;
	if(check_diag(sudoku) == false) return false;
	return true;
}

bool read_sudoku(char sudoku[SUDOKU_SIZE][SUDOKU_SIZE]){
	string temp;
	for (int line = 0; line < SUDOKU_SIZE; line++){
		cin >> temp;
		if (temp.size() < SUDOKU_SIZE){
			line--;
			continue;
		}
		int col = 0;
		for(int index = 0; index < temp.size(); index++){
			if(col >= SUDOKU_SIZE)
				return false;
			if(isdigit(temp[index])){
				sudoku[line][col++] = temp[index];
			}else if(temp[index] == '?'){
				sudoku[line][col++] = '0';
			}else if(temp[index] == ' '){
				continue;
			}else{
				return false;
			}
		}	

	}
	return true;
}

void print_sudoku(char sudoku[SUDOKU_SIZE][SUDOKU_SIZE]){
	for(int line = 0; line < SUDOKU_SIZE; line++){
		for(int col = 0; col < SUDOKU_SIZE; col++){
			cout << sudoku[line][col];
		}
		cout << "\n";
	}
}
