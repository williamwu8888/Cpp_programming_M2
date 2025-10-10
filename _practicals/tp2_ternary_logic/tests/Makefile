CC = g++
CCFLAGS = -Wall -Werror -std=c++11 -g -I../headers

# Source files from ../file/ directory
SRC_DIR = ../file
SRC = $(wildcard $(SRC_DIR)/*.cc)
OBJ = $(SRC:$(SRC_DIR)/%.cc=%.o)

# Test files from current directory  
TST = $(wildcard *.cc)
OBJ_TEST = $(filter-out main.o, $(OBJ)) $(TST:.cc=.o)

testcase: $(OBJ_TEST) 
	$(CC) $(CCFLAGS) -o $@ $^

# Rule for source files in ../file/ directory
%.o: $(SRC_DIR)/%.cc
	$(CC) $(CCFLAGS) -c $< -o $@

# Rule for test files in current directory
%.o: %.cc
	$(CC) $(CCFLAGS) -c $< -o $@

./clean:
	del *.o *.exe *.out
	
cleantest:
	cd $(TST_DIR); make clean
	
distclean : clean cleantest

.PHONY: clean