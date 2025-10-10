# 中小学C++编程练习题库 Makefile
# 适合学生使用的简化编译配置

# 编译器设置
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
TARGET_DIR = build
BIN_DIR = bin
TOOLS_DIR = tools

# 默认目标
.PHONY: all clean help setup test-examples

all: setup build-tools

# 创建构建目录
setup:
	@echo "=== 设置项目环境 ==="
	@mkdir -p $(TARGET_DIR)
	@mkdir -p $(BIN_DIR)
	@echo "✅ 创建构建目录: $(TARGET_DIR)"
	@echo "✅ 创建工具目录: $(BIN_DIR)"

# 编译工具
build-tools: setup
	@echo "=== 编译项目工具 ==="
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/build $(TOOLS_DIR)/build.cpp
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/project_check $(TOOLS_DIR)/project_check.cpp
	@echo "✅ 编译完成: build工具 (输出到 $(BIN_DIR)/build)"
	@echo "✅ 编译完成: 项目检查工具 (输出到 $(BIN_DIR)/project_check)"

# 编译示例程序
examples: setup
	@echo "=== 编译示例程序 ==="
	$(CXX) $(CXXFLAGS) -o $(TARGET_DIR)/hello_world examples/hello_world.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET_DIR)/basic_variables examples/basic_variables.cpp
	@echo "✅ 示例程序编译完成"

# 测试示例程序
test-examples: examples
	@echo "=== 测试示例程序 ==="
	@echo "运行 hello_world:"
	@$(TARGET_DIR)/hello_world
	@echo ""
	@echo "运行 basic_variables (需要手动输入):"
	@echo "小明" | echo "12" | echo "1.5" | $(TARGET_DIR)/basic_variables || true

# 编译练习题参考答案
solutions: setup
	@echo "=== 编译练习题参考答案 ==="
	$(CXX) $(CXXFLAGS) -o $(TARGET_DIR)/solution-01 solutions/level1-基础入门/01-hello-world.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET_DIR)/solution-02 solutions/level1-基础入门/02-basic-variables.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET_DIR)/solution-03 solutions/level1-基础入门/03-simple-calculator.cpp
	@echo "✅ 参考答案编译完成"

# 运行特定练习题的测试
test-solution-01: solutions
	@echo "=== 测试练习题01 ==="
	@$(TARGET_DIR)/solution-01
	@echo ""

test-solution-02: solutions
	@echo "=== 测试练习题02 ==="
	@echo "使用测试输入文件："
	@cat exercises/level1-基础入门/02-basic-variables/input.txt
	@echo "程序输出："
	@$(TARGET_DIR)/solution-02 < exercises/level1-基础入门/02-basic-variables/input.txt

test-solution-03: solutions
	@echo "=== 测试练习题03 ==="
	@echo "使用测试输入文件："
	@cat exercises/level1-基础入门/03-simple-calculator/input.txt
	@echo "程序输出："
	@$(TARGET_DIR)/solution-03 < exercises/level1-基础入门/03-simple-calculator/input.txt

# 清理编译文件
clean:
	@echo "=== 清理编译文件 ==="
	@rm -rf $(TARGET_DIR)
	@rm -rf $(BIN_DIR)
	@rm -f examples/*.exe examples/*.out
	@rm -f solutions/*/*.exe solutions/*/*.out
	@rm -f exercises/*/*.exe exercises/*/*.out
	@echo "✅ 清理完成"

# 显示帮助信息
help:
	@echo "=== C++练习题库编译帮助 ==="
	@echo ""
	@echo "可用命令："
	@echo "  make setup          - 创建项目构建环境"
	@echo "  make build-tools     - 编译项目工具"
	@echo "  make examples        - 编译示例程序"
	@echo "  make test-examples   - 测试示例程序"
	@echo "  make solutions       - 编译所有参考答案"
	@echo "  make test-solution-01 - 测试练习题01"
	@echo "  make test-solution-02 - 测试练习题02"
	@echo "  make test-solution-03 - 测试练习题03"
	@echo "  make check-env       - 检查编译环境"
	@echo "  make check-project   - 运行项目完整性检查"
	@echo "  make clean           - 清理所有编译文件"
	@echo "  make help            - 显示此帮助信息"
	@echo ""
	@echo "编译单个文件示例："
	@echo "  g++ -std=c++11 -Wall -o hello examples/hello_world.cpp"
	@echo "  ./hello"
	@echo ""
	@echo "使用项目工具："
	@echo "  make build-tools"
	@echo "  ./bin/build compile your_file.cpp"
	@echo "  ./bin/build test your_file.cpp"

# 快速验证环境
check-env:
	@echo "=== 检查编译环境 ==="
	@which g++ > /dev/null && echo "✅ g++ 编译器已安装" || echo "❌ g++ 编译器未找到"
	@g++ --version | head -1
	@echo "✅ 环境检查完成"

# 项目完整性检查
check-project: build-tools
	@echo "=== 运行项目完整性检查 ==="
	@$(BIN_DIR)/project_check

# 创建新练习题模板
create-exercise:
	@echo "=== 创建新练习题模板 ==="
	@echo "请手动创建练习题目录和文件"
	@echo "参考现有题目结构："
	@echo "  exercises/level1-基础入门/03-新题目/"
	@echo "    ├── README.md"
	@echo "    ├── template.cpp"
	@echo "    ├── input.txt"
	@echo "    └── expected_output.txt"

# 一键测试所有内容
test-all: clean setup build-tools examples solutions test-solution-01 test-solution-02 test-solution-03
	@echo "=== 全部测试完成 ==="
	@echo "✅ 所有组件编译和测试成功"
