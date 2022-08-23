CC=g++
CPP_FLAGS=-std=c++14 -g -Wall
CPP_FLAGS=-std=c++14 -O2
SRCS=$(wildcard *.cpp)
OBJ_D=obj
OBJS=$(patsubst %.cpp, $(OBJ_D)/%.o, $(SRCS))
BIN_D=bin
BIN=$(BIN_D)/simulador
ZIPNAME=T2_TR1_Luiz_190055171.zip

all: $(BIN)

release: CPP_FLAGS=-std=c++14 -O2 -DNDEBUG
release: clean $(BIN)

$(BIN): mkbin $(OBJS)
	$(CC) $(CPP_FLAGS) $(OBJS) -o $@

$(OBJ_D)/%.o: %.cpp | mkobj
	$(CC) $(CPP_FLAGS) -c $< -o $@

.PHONY: mkbin mkobj clean submit

mkbin:
	mkdir -p $(BIN_D)

mkobj:
	mkdir -p $(OBJ_D)

clean:
	rm -rf $(BIN_D) $(OBJ_D)

submit: clean
	rm -f $(ZIPNAME)
	zip $(ZIPNAME) *
