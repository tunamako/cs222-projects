ifeq ($(OS),Darwin)
CC=clang
CXX=clang++
else
CC=gcc
CXX=g++
endif

GTEST_DIR=../googletest-master/googletest
GTEST_INC_DIR=$(GTEST_DIR)/include
CFLAGS=-g -std=c99 -I$(GTEST_INC_DIR)


CPPFLAGS += -g -Wall -isystem $(GTEST_INC_DIR)
CXXFLAGS += -Wextra -pthread

GTEST_HEADERS = $(GTEST_INC_DIR)/gtest/*.h \
                $(GTEST_INC_DIR)/gtest/internal/*.h

ifeq ($(OS),Windows_NT)
all: testRunner.exe
else
all: testRunner
endif

ifeq ($(OS),Windows_NT)
clean: 
	rm *.o testRunner.exe
else
clean: 
	rm *.o testRunner
endif

ifeq ($(OS),Windows_NT)
testRunner.exe: adt.o csString.o hashTable.o gtest-all.o test_adt.o gtest_main.o
	$(CXX) -o testRunner adt.o csString.o hashTable.o gtest-all.o test_adt.o gtest_main.o -lpthread
else
testRunner: adt.o csString.o hashTable.o gtest-all.o test_adt.o gtest_main.o
	$(CXX) -o testRunner adt.o csString.o hashTable.o gtest-all.o test_adt.o gtest_main.o -lpthread
endif

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

adt.o: adt.h adt.c
	$(CC) $(CFLAGS) -c adt.c -o adt.o

csString.o: csString.h csString.c
	$(CC) $(CFLAGS) -c csString.c -o csString.o

hashTable.o: hashTable.h hashTable.c
	$(CC) $(CFLAGS) -c hashTable.c -o hashTable.o

test_adt.o: test_adt.cc
	$(CXX) $(CPPFLAGS) -c test_adt.cc -o test_adt.o

gtest_main.o: gtest_main.cc
	$(CXX) $(CPPFLAGS) -c gtest_main.cc -o gtest_main.o
