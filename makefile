test : main.o vectorTest.o alloc.o
	g++ -O2 -std=gnu++11 -o test main.o vectorTest.o alloc.o

main.o : main.cpp .\test\vectorTest.h
	g++ -std=gnu++11 -c main.cpp

vectorTest.o : .\test\vectorTest.cpp .\test\vectorTest.h
	g++ -std=gnu++11 -c .\test\vectorTest.cpp

alloc.o : alloc.cpp alloc.h
	g++ -std=gnu++11 -c alloc.cpp
clean : 
	rm test.exe main.o vectorTest.o alloc.o