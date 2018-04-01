include_directories(./)

set(SUDOKU_BASIC_CODE
  ./sudoku_basic.cpp
)

add_library(Sudoku
	SHARED
	${SUDOKU_BASIC_CODE}
)

