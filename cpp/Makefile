CXX = g++
CXXFLAGS = -O3 -use_fast_math -flto -DNDEBUG -march=native -mtune=native -Wall -Wextra -std=c++23
EXE = prison_problem
HEADERS = src/*.hpp
SRCS = src/*.cpp

.PHONY: all clean

all:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXE)

clean:
	rm -f prison_problem