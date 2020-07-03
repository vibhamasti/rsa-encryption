# Makefile for text-encryption
# *****************************************************
# Variables to control Makefile operation

CXX = g++ -std=c++11
CXXFLAGS = -Wall -g
OBJFILES = obj/main.o obj/helpers.o obj/encryption.o obj/user.o
HEADERS = include/*
INC = -I./include
TARGET = a.out

# ****************************************************
# Targets needed to bring the executable up to date

$(TARGET): $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJFILES)

default: $(TARGET)

obj/main.o: src/main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INC) -c src/main.cpp -o $@

obj/encryption.o: src/encryption.cpp include/helpers.h
	$(CXX) $(CXXFLAGS) $(INC) -c src/encryption.cpp -o $@

obj/helpers.o: src/helpers.cpp include/helpers.h
	$(CXX) $(CXXFLAGS) $(INC) -c src/helpers.cpp -o $@

obj/user.o: src/user.cpp include/user.h include/encryption.h
	$(CXX) $(CXXFLAGS) $(INC) -c src/user.cpp -o $@

clean:
	rm -f $(OBJFILES) $(TARGET) *~