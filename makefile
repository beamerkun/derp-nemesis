all: name

name: main.cpp
	g++ main.cpp -std=c++11 -g -o name	

clean:
	rm -rf name
