# Makefile for text-encryption
# *****************************************************
# Variables to control Makefile operation

CXX = g++ -std=c++11
CXXFLAGS = -Wall -g
OBJFILES = main.o helpers.o encryption.o user.o
TARGET = a.out

# ****************************************************
# Targets needed to bring the executable up to date

$(TARGET): $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJFILES)


main.o: main.cpp helpers.h encryption.h user.h
	$(CXX) $(CXXFLAGS) -c main.cpp

encryption.o: encryption.h helpers.h

helpers.o: helpers.h

user.o: encryption.h

clean:
	rm -f $(OBJFILES) $(TARGET) *~