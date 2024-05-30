CXX = clang++
CXXFLAGS = -O3 -DNDEBUG -march=native -Wall -Wextra -std=c++23
EXE = prison_problem
HEADERS = src/*.hpp
SRCS = src/*.cpp

.PHONY: all clean

all:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXE)

clean:
	rm -f prison_problem