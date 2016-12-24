stl : main.o listTest.o vectorTest.o alloc.o dequeTest.o
	g++ -g -std=c++11 -o stl main.o listTest.o vectorTest.o alloc.o dequeTest.o

main.o : main.cpp ./test/listTest.h ./test/vectorTest.h 
	g++ -g -std=c++11 -c main.cpp

listTest.o : ./test/listTest.cpp ./test/listTest.h 
	g++ -g -std=c++11 -c ./test/listTest.cpp

vectorTest.o : ./test/vectorTest.cpp ./test/vectorTest.h 
	g++ -g -std=c++11 -c ./test/vectorTest.cpp

dequeTest.o : ./test/dequeTest.cpp ./test/dequeTest.h
	g++ -g -std=c++11 -c ./test/dequeTest.cpp

alloc.o : alloc.cpp alloc.h
	g++ -g -std=c++11 -c alloc.cpp
clean : 
	rm stl main.o listTest.o vectorTest.o alloc.o dequeTest.o
