#Makefile for Futures Trader
CC = g++
INC = -I../include
LIB = -L../lib -lthosttraderapi64
SRC = main.cpp CtpTraderSpi.cpp CSem.cpp
BIN = ../bin
CFLAGS = -g -Wall   -fPIC
CPPFLAGS = -g -Wall   -fPIC

TARGET = TestTrader

all:$(TARGET)
	cp $(TARGET) $(BIN)
$(TARGET):$(SRC)
	g++ $(CFLAGS) -o $(TARGET) $(INC) $(SRC) $(LIB)
clean:
	rm -f $(BIN)/* *.o $(TARGET)
