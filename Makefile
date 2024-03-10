CC = g++
CLFAGS = -Wall -std=c++11 -g

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

log: log.o
	$(CC) $(CLFAGS) -o bin/log $(OBJ_DIR)/log.o

log.o: $(SRC_DIR)/log.cpp
	$(CC) $(CLFAGS) -c $(SRC_DIR)/log.cpp -o $(OBJ_DIR)/log.o