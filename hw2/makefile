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


CPPFLAGS += -std=c++11 -g -Wall -isystem $(GTEST_INC_DIR)
CXXFLAGS += -std=c++11 -Wextra -pthread

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
testRunner.exe: gtest-all.o test_hw.o gtest_main.o binaryTree.o
	$(CXX) -o testRunner binaryTree.o gtest-all.o test_hw.o gtest_main.o -lpthread
else
testRunner: gtest-all.o test_hw.o gtest_main.o binaryTree.o
	$(CXX) -o testRunner binaryTree.o gtest-all.o test_hw.o gtest_main.o -lpthread
endif

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

test_hw.o: test_hw.cc
	$(CXX) $(CPPFLAGS) -c test_hw.cc -o test_hw.o

gtest_main.o: gtest_main.cc
	$(CXX) $(CPPFLAGS) -c gtest_main.cc -o gtest_main.o

binaryTree.o: binaryTree.cc binaryTree.h
	$(CXX) $(CXXFLAGS) -c binaryTree.cc -o binaryTree.o
