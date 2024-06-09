#!make -f

CXX=g++
CXXFLAGS=-std=c++14 -Werror 
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=player.cpp tile.cpp cardType.hpp deck.cpp main.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

main:tile.cpp cardType.hpp main.cpp board.cpp
	$(CXX) $^ -o main.exe
	./main.exe


test: Algorithms.cpp Graph.cpp Test.cpp
	$(CXX) $^ -o test.exe
	./test.exe

testCounter: TestCounter.o Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o testCounter.exe
	./testCounter.exe

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrindTest: test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test.exe 2>&1 | { egrep "lost| at " || true; }

valgrindTestCounter: testCounter.exe
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./testCounter.exe 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@