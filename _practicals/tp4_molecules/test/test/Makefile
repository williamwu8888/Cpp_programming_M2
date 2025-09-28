CC=g++
CCFLAGS= -Wall -Werror -std=c++20 -g
SRC= $(wildcard *.cc)
OBJ= $(SRC:.cc=.o)
TST= $(wildcard *.cc)
OBJ_MAIN= $(filter-out TestCase.o,  $(OBJ)) 
OBJ_TEST = $(filter-out main.o, $(OBJ)) 

all: testcase

run: testcase
	./testcase

testcase : $(OBJ_TEST) 
	$(CC) $(CCFLAGS)  -o $@ $^

main: $(OBJ_MAIN)
	$(CC) $(CCFLAGS) -o $@ $^

%.o: %.cc
	$(CC) $(CCFLAGS)  -I./ -o $@ -c $<

clean :
	rm -f $(OBJ_TEST) testcase