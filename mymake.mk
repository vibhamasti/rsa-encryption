# Makefile for text-encryption
# *****************************************************
# Variables to control Makefile operation

CXX = g++ -std=c++11
CXXFLAGS = -Wall -g
OBJFILES = main.o rsa.o helpers.o rc4.o
TARGET = a.out

# ****************************************************
# Targets needed to bring the executable up to date

$(TARGET): $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJFILES)


main.o: main.cpp rsa.h helpers.h rc4.h
	$(CXX) $(CXXFLAGS) -c main.cpp

rsa.o: rsa.h helpers.h

helpers.o: helpers.h

rc4.o: rc4.h helpers.h

clean:
	rm -f $(OBJFILES) $(TARGET) *~