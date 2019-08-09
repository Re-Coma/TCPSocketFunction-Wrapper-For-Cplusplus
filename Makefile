CC=gcc
CXX=g++ -g
CXXFLAGS= -std=c++17

TEST_TARGET=test

SRCS=$(wildcard SockWrapper/*.cpp)

TEST_SRC = test.cpp

OBJS=$(SRCS:.cpp=.o)
TEST_OBJ=$(TEST_SRC:.cpp=.o)

test: $(OBJS) $(TEST_OBJ)
	g++ -o $(TEST_TARGET) $(OBJS) $(TEST_OBJ)

clean_test:
	rm $(OBJS)
	rm $(TEST_OBJ)
	rm $(TEST_TARGET)
