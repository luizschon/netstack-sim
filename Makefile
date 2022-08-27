SRC_D=src
IMGUI_D=3rd_party/imgui
IMGUI_BACK_D=$(IMGUI_D)/backends
OBJ_D=obj
BIN_D=bin

CXX=g++
CXX_FLAGS=-std=c++14 -g -Wall
CXX_FLAGS+=-I$(IMGUI_D) -I$(IMGUI_BACK_D) `sdl2-config --cflags`
LIBS=-lGL -ldl `sdl2-config --libs`

SRCS=$(wildcard $(SRC_D)/*.cpp)
SRCS+= $(IMGUI_D)/imgui.cpp $(IMGUI_D)/imgui_demo.cpp $(IMGUI_D)/imgui_draw.cpp $(IMGUI_D)/imgui_tables.cpp $(IMGUI_D)/imgui_widgets.cpp
SRCS+= $(IMGUI_BACK_D)/imgui_impl_sdl.cpp $(IMGUI_BACK_D)/imgui_impl_opengl3.cpp
OBJS=$(addprefix $(OBJ_D)/, $(addsuffix .o, $(basename $(notdir $(SRCS)))))
BIN=$(BIN_D)/simulador
ZIPNAME=T2_TR1_Luiz_190055171.zip

all: $(BIN)

release: CXX_FLAGS=-std=c++14 -O2 -DNDEBUG
release: CXX_FLAGS+=-I$(IMGUI_DIR) -I$(IMGUI_BACK_DIR) `sdl2-config --cflags`
release: clean $(BIN)

$(BIN): $(OBJS) mkbin
	$(CXX) $(CXX_FLAGS) $(OBJS) $(LIBS) -o $@
	@echo "Build completa!"
	@echo "Rode com bin/simulador"

$(OBJ_D)/%.o: $(SRC_D)/%.cpp | mkobj
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(OBJ_D)/%.o: $(IMGUI_D)/%.cpp | mkobj
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(OBJ_D)/%.o: $(IMGUI_BACK_D)/%.cpp | mkobj
	$(CXX) $(CXX_FLAGS) -c $< -o $@

.PHONY: mkbin mkobj clean submit

mkbin:
	mkdir -p $(BIN_D)

mkobj:
	mkdir -p $(OBJ_D)

clean:
	rm -rf $(BIN_D) $(OBJ_D)

submit: clean
	rm -f $(ZIPNAME)
	zip -r $(ZIPNAME) *
