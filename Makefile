CXX = g++
CXXFLAGS = -std=c++17 -Wall

main: main.cpp src/parse.cpp src/read_file.cpp
	$(CXX) $(CXXFLAGS) main.cpp src/parse.cpp src/read_file.cpp -o main
