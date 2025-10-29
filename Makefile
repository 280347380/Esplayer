# Esplayer Makefile
# 编译器设置
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
INCLUDES = -Iinclude

# 目录设置
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# 源文件和目标文件
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TARGET = $(BIN_DIR)/esplayer

# 默认目标
all: directories $(TARGET)

# 创建必要的目录
directories:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJECTS)
	@echo "Linking $@..."
	@$(CXX) $(OBJECTS) -o $@
	@echo "Build complete: $@"

# 编译源文件生成目标文件
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# 清理编译文件
clean:
	@echo "Cleaning build files..."
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Clean complete."

# 重新编译
rebuild: clean all

# 运行程序
run: $(TARGET)
	@echo "Running $(TARGET)..."
	@./$(TARGET)

# 安装（可选）
install: $(TARGET)
	@echo "Installing to /usr/local/bin..."
	@sudo cp $(TARGET) /usr/local/bin/

# 显示帮助信息
help:
	@echo "Available targets:"
	@echo "  all      - Build the project (default)"
	@echo "  clean    - Remove build files"
	@echo "  rebuild  - Clean and build"
	@echo "  run      - Build and run the program"
	@echo "  install  - Install to system"
	@echo "  help     - Show this help message"

# 声明伪目标
.PHONY: all clean rebuild run install help directories