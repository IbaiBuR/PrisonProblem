CXX     = g++
SRCS    = src/*.cpp
HEADERS = src/*.hpp

STD      = -std=c++23
WARNINGS = -Wall -Wextra -Wpedantic
CXXFLAGS = -O3 -funroll-loops -flto=auto -DNDEBUG -march=native -mtune=native $(STD) $(WARNINGS)
LDFLAGS  = -ltbb

EXE = prison_problem

.PHONY: all clean

all:
	$(CXX) $(CXXFLAGS) $(SRCS) $(LDFLAGS) -o $(EXE)

clean:
	rm -f prison_problem