FLAGS = -O3 -pthread -std=gnu++0x -fopenmp
CPPFILES = main.cpp gauss.cpp

all : gauss

gauss : main.cpp gauss.cpp
	g++ $(FLAGS) -o gauss $(CPPFILES)

run : small medium big

small : gauss
	./gauss 4

medium : gauss
	./gauss 100

big : gauss
	./gauss 1000

huge : gauss
	./gauss 10000

clean :
	rm -rf *.o gauss
