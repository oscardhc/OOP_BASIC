CXX = g++
CXXFLAGS = -Wall -std=c++11 -g

code : OOP_BASIC/main.cpp OOP_BASIC/Parser.cpp OOP_BASIC/Expression.cpp OOP_BASIC/Program.cpp
	$(CXX) -o code $^ $(CXXFLAGS)

clean:
	rm score -f
