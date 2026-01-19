# DoomLike Makefile
# - Compila .o em build/
# - Linka o executável em build/DoomLike
# - Copia assets/maps/shaders para dentro de build/ (build portátil)
# - make run já prepara tudo e executa

CXX       := g++
CXXFLAGS  := -g -O0 -Wall -Wextra -Iinclude
LDFLAGS   :=
LDLIBS    := -lGLEW -lGL -lGLU -lglut

TARGET    := DoomLike
BUILD_DIR := build

SRC_DIR   := src
MAIN      := main.cpp

# Encontra todos os .cpp dentro de src (recursivo)
SRCS      := $(shell find $(SRC_DIR) -name '*.cpp' | sort)
SRCS      += $(MAIN)

# Converte paths em nomes de objetos dentro de build/
OBJS      := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))

.PHONY: all clean run dirs stage

# Build padrão já gera build pronta para rodar/entregar
all: $(BUILD_DIR)/$(TARGET) stage

$(BUILD_DIR)/$(TARGET): dirs $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

# Regra genérica: compila qualquer .cpp para build/.../.o
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

dirs:
	@mkdir -p $(BUILD_DIR)

# Copia recursos para dentro de build/ (self-contained)
stage: dirs
	@rm -rf $(BUILD_DIR)/assets $(BUILD_DIR)/maps $(BUILD_DIR)/shaders
	@cp -r assets  $(BUILD_DIR)/
	@cp -r maps    $(BUILD_DIR)/
	@cp -r shaders $(BUILD_DIR)/

# Roda SEM depender do cwd externo
run: all
	cd $(BUILD_DIR) && ./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
