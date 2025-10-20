# C++ 贪食蛇游戏 Makefile

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# 目标文件
TARGET = snake_game_cross_platform

# 默认目标
all: $(TARGET)

# 跨平台版本贪食蛇游戏
$(TARGET): snake_game_cross_platform.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# 清理编译文件
clean:
	rm -f $(TARGET)
	rm -f *.exe

# 运行游戏
run: $(TARGET)
	./$(TARGET)

# 安装依赖（如果需要）
install-deps:
	@echo "No additional dependencies required for this project"

# 帮助信息
help:
	@echo "Available targets:"
	@echo "  all                   - Build the game"
	@echo "  $(TARGET)             - Build cross-platform version"
	@echo "  run                   - Run the game"
	@echo "  clean                 - Remove compiled files"
	@echo "  help                  - Show this help message"

.PHONY: all clean run install-deps help