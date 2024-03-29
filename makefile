all: generate transform solve

generate: sudoku.o generate.o
	g++ -o generate sudoku.o generate.o

transform: sudoku.o transform.o
	g++ -o transform sudoku.o transform.o

solve: sudoku.o solve.o
	g++ -o solve sudoku.o solve.o

sudoku.o: sudoku.cpp sudoku.h
	g++ -c sudoku.cpp

generate.o: generate.cpp sudoku.h
	g++ -c generate.cpp

transform.o: transform.cpp sudoku.h
	g++ -c transform.cpp

solve.o: solve.cpp sudoku.h
	g++ -c solve.cpp

clean:
	rm generate transform solve *.o


