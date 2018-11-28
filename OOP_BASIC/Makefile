CXX = g++
CXXFLAGS = -Wall -O2 -std=c++11

code : main.cpp Parser.cpp Expression.cpp Program.cpp
	$(CXX) -o code $^ $(CXXFLAGS)

clean:
	rm score -f
