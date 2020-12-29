build:
	clear
	rm -f tests.exe
	g++ tests.cpp -o tests.exe -lgtest -lgtest_main -lpthread
	./tests.exe
	
run:
	./tests.exe

valgrind:
	clear
	rm -f tests.exe
	g++ tests.cpp -o tests.exe -lgtest -lgtest_main -lpthread
	valgrind --track-origins=yes --tool=memcheck --leak-check=full ./tests.exe
	
gdb:
	clear
	rm -f tests.exe
	g++ tests.cpp -o tests.exe -lgtest -lgtest_main -lpthread -g
	gdb tests.exe