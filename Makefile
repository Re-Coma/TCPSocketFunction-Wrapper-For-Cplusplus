CC=gcc
CXX=g++ -g
CXXFLAGS= -std=c++17 

SERVER=server
CLIENT=client

SRCS=$(wildcard SockWrapper/*.cpp)

CLIENT_SRC = client.cpp
SERVER_SRC = server.cpp

OBJS=$(SRCS:.cpp=.o)

SERVER_OBJ=server.o
CLIENT_OBJ=client.o

all_test: server client
server: $(OBJS) $(SERVER_OBJ)
	g++ -o $(SERVER) $(OBJS) $(SERVER_OBJ)

client: $(OBJS) $(CLIENT_OBJ)
	g++ -o $(CLIENT) $(OBJS) $(CLIENT_OBJ)

clean_test:
	rm $(OBJS)
	rm $(SERVER_OBJ)
	rm $(CLIENT_OBJ)
	rm $(SERVER)
	rm $(CLIENT)
