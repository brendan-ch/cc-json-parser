CXX = g++
CXXFLAGS = -std=c++17 -Wall
DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CXXFLAGS += -g
endif

main: main.cpp src/parse.cpp src/read_file.cpp
	$(CXX) $(CXXFLAGS) main.cpp src/parse.cpp src/read_file.cpp -o main
