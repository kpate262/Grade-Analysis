all:
	rm -f proj3.exe
	g++ -g -std=c++11 -Wall main.cpp gradeutil.cpp -o proj3.exe
	./proj3.exe