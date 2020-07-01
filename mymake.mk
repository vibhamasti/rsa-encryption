# Makefile for Writing Make Files Example
# *****************************************************
# Variables to control Makefile operation

CXX = g++ -std=c++11
CXXFLAGS = -Wall -g
OBJFILES = main.o rsa.o randomprime.o rc4.o
TARGET = a.out

# ****************************************************
# Targets needed to bring the executable up to date

$(TARGET): $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJFILES)

# The main.o target can be written more simply

main.o: main.cpp rsa.h randomprime.h rc4.h
	$(CXX) $(CXXFLAGS) -c main.cpp

rsa.o: rsa.h randomprime.h

randomprime.o: randomprime.h

rc4.o: rc4.h

clean:
	rm -f $(OBJFILES) $(TARGET) *~