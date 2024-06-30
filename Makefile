# #!make -f
# #Mail : yonidil1997@gmail.com
# #ID : 316529445

CXX=g++
CXXFLAGS=-std=c++14 -Werror 
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=tile.cpp main.cpp board.cpp deck.cpp catan.cpp player.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

.PHONI: cleen all valgrind run

all:$(SOURCES)
	$(CXX) $^ -o main.exe
	
run:
	./main.exe

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

cleen:
	rm -f *.o main.exe

valgrind:$(SOURCES)
	valgrind $(VALGRIND_FLAGS) ./main.exe