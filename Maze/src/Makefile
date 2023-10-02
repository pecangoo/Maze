REPORTFOLDER = report/

all: install

install:
	cd source; qmake; make

run: 
	ls
	cd source;	./maze.app/Contents/MacOS/maze
	
uninstall: clean

tests: clean
	g++ -c  ./source/eller.cpp -lgtest -lgtest_main -pthread --coverage
	g++ -o run_test *.o ./tests/start_test.cc  -lgtest -lgtest_main -pthread  --coverage
	./run_test

clean:
	rm -rf *.o run_test *.gcno report *.gcda
	cd source; make clean; rm -rf maze.app .qmake.stash maze
	find . -name .DS_Store -type f -delete
	
gcov_report: tests
	mkdir -p gcov/
	mkdir report/
	lcov -t "s21_matrix_oop.a" -o run_test -c -d .
	genhtml run_test -o $(REPORTFOLDER)
	xdg-open $(REPORTFOLDER)index.html

push:
	git add --all
	git commit -ms
	git push --all

dvi:
	rm -rf html
	cd source && doxygen *.cpp
	cd source && open html/index.html

dist: uninstall clean
	tar -cf ./A1_Maze_Super_Mouse.tar * 
