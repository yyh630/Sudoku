const int SUDOKU_SIZE = 9;
const int SUDOKU_BOX_SIZE = 3;

bool read_sudoku(char sudoku[SUDOKU_SIZE][SUDOKU_SIZE]);
void print_sudoku(char sudoku[SUDOKU_SIZE][SUDOKU_SIZE]);

//sudoku only contain character '0'~'9'
bool check_sudoku(char sudoku[SUDOKU_SIZE][SUDOKU_SIZE]);

//using to check the diag in the sudoku matrix
bool check_diag_sudoku(char sudoku[SUDOKU_SIZE][SUDOKU_SIZE]);

