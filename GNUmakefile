PPO_MKDIR = MKDIR
PPO_CLEAN = CLEAN
PPO_CXX   = CXX
PPO_CC    = CC
PPO_AR    = AR

VENDOR_DIR = vendor
BUILD_DIR  = build
HDR_DIR    = include
SRC_DIR    = src

LUNA_HDR_DIR   = $(HDR_DIR)
LUNA_SRC_DIR   = $(SRC_DIR)
LUNA_BUILD_DIR = $(BUILD_DIR)
LUNA_SRCS     := $(wildcard $(LUNA_SRC_DIR)/*.cc)
LUNA_OBJS     := $(patsubst $(LUNA_SRC_DIR)/%.cc, $(LUNA_BUILD_DIR)/%.o, $(LUNA_SRCS))

GLFW_HDR_DIR   = $(VENDOR_DIR)/glfw/$(HDR_DIR)
GLFW_SRC_DIR   = $(VENDOR_DIR)/glfw/$(SRC_DIR)
GLFW_BUILD_DIR = $(BUILD_DIR)/glfw
GLFW_SRCS     := $(wildcard $(GLFW_SRC_DIR)/*.c)
GLFW_OBJS     := $(patsubst $(GLFW_SRC_DIR)/%.c, $(GLFW_BUILD_DIR)/%.o, $(GLFW_SRCS))

IMGUI_HDR_DIR        = $(VENDOR_DIR)/imgui
IMGUI_SRC_DIR        = $(VENDOR_DIR)/imgui
IMGUI_BUILD_DIR      = $(BUILD_DIR)/imgui
IMGUI_SRCS          := $(wildcard $(IMGUI_SRC_DIR)/*.cpp)
IMGUI_OBJS          := $(patsubst $(IMGUI_SRC_DIR)/%.cpp, $(IMGUI_BUILD_DIR)/%.o, $(IMGUI_SRCS))
IMGUI_BACK_HDR_DIR   = $(IMGUI_HDR_DIR)/backends
IMGUI_BACK_SRC_DIR   = $(IMGUI_SRC_DIR)/backends
IMGUI_BACK_BUILD_DIR = $(IMGUI_BUILD_DIR)/backends
IMGUI_BACK_SRCS      = $(IMGUI_BACK_SRC_DIR)/imgui_impl_glfw.cpp $(IMGUI_BACK_SRC_DIR)/imgui_impl_opengl3.cpp
IMGUI_BACK_OBJS     := $(patsubst $(IMGUI_BACK_SRC_DIR)/%.cpp, $(IMGUI_BACK_BUILD_DIR)/%.o, $(IMGUI_BACK_SRCS))

STB_HDR_DIR = $(VENDOR_DIR)/stb

AR  = ar -rc
CC  = clang
CXX = clang++

OPTIMIZATIONS = -pipe -O3

GLFW_CPPFLAGS  = -D _GLFW_X11
IMGUI_CPPFLAGS = -isystem $(IMGUI_HDR_DIR) -isystem $(GLFW_HDR_DIR)
LUNA_CPPFLAGS  = -I $(LUNA_HDR_DIR) -isystem $(STB_HDR_DIR) -isystem $(GLFW_HDR_DIR) -isystem $(IMGUI_HDR_DIR)

GLFW_CFLAGS    = $(OPTIMIZATIONS)
IMGUI_CXXFLAGS = $(OPTIMIZATIONS)
LUNA_CXXFLAGS  = -std=c++20 -Wall -Wextra -pedantic -Werror $(OPTIMIZATIONS)

OUT = libluna.a

.PHONY: all clean mrproper

all: $(LUNA_BUILD_DIR) $(GLFW_BUILD_DIR) $(IMGUI_BUILD_DIR) $(IMGUI_BACK_BUILD_DIR) $(OUT)
	@:

$(LUNA_BUILD_DIR):
	@echo "  $(PPO_MKDIR)   $@"
	@mkdir -p $@

$(GLFW_BUILD_DIR):
	@echo "  $(PPO_MKDIR)   $@"
	@mkdir -p $@

$(IMGUI_BUILD_DIR):
	@echo "  $(PPO_MKDIR)   $@"
	@mkdir -p $@

$(IMGUI_BACK_BUILD_DIR):
	@echo "  $(PPO_MKDIR)   $@"
	@mkdir -p $@

$(OUT): $(GLFW_OBJS) $(IMGUI_OBJS) $(IMGUI_BACK_OBJS) $(LUNA_OBJS)
	@echo "  $(PPO_AR)      $@"
	@$(AR) $@ $^

$(LUNA_BUILD_DIR)/%.o: $(LUNA_SRC_DIR)/%.cc
	@echo "  $(PPO_CXX)     $@"
	@$(CXX) $(LUNA_CPPFLAGS) $(LUNA_CXXFLAGS) -c -MD $< -o $@

$(GLFW_BUILD_DIR)/%.o: $(GLFW_SRC_DIR)/%.c
	@echo "  $(PPO_CC)      $@"
	@$(CC) $(GLFW_CPPFLAGS) $(GLFW_CFLAGS) -c -MD $< -o $@

$(IMGUI_BUILD_DIR)/%.o: $(IMGUI_SRC_DIR)/%.cpp
	@echo "  $(PPO_CXX)     $@"
	@$(CXX) $(IMGUI_CXXFLAGS) -c -MD $< -o $@

$(IMGUI_BACK_BUILD_DIR)/%.o: $(IMGUI_BACK_SRC_DIR)/%.cpp
	@echo "  $(PPO_CXX)     $@"
	@$(CXX) $(IMGUI_CPPFLAGS) $(IMGUI_CXXFLAGS) -c -MD $< -o $@

-include $(LUNA_BUILD_DIR)/*.d
-include $(GLFW_BUILD_DIR)/*.d
-include $(IMGUI_BUILD_DIR)/*.d
-include $(IMGUI_BACK_BUILD_DIR)/*.d

clean:
	@if [ -d $(LUNA_BUILD_DIR) ]; then           \
	  echo "  $(PPO_CLEAN)   $(LUNA_BUILD_DIR)"; \
	  rm -r $(LUNA_BUILD_DIR);                   \
	fi

mrproper: clean
	@if [ -e $(OUT) ]; then           \
	  echo "  $(PPO_CLEAN)   $(OUT)"; \
	  rm $(OUT);                      \
	fi
