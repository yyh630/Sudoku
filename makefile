all:
	cd build; /usr/local/bin/cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -Wc++11-extensions ../src; make;


clean:
	rm -r -f build
	mkdir build

test:
	./build/sudoku_check < data/test01.in > data/ans01.out
	./build/sudoku_check < data/test02.in > data/ans02.out
	diff data/ans01.out data/test01.out
	diff data/ans02.out data/test02.out

