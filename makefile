all: name

name: main.cpp
	g++ main.cpp -std=c++11 -g -o derp-nemesis	

clean:
	rm -rf derp-nemesis
