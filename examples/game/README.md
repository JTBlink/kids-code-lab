# C++ 贪食蛇游戏

这是一个用C++编写的经典贪食蛇游戏，采用跨平台设计，支持Windows、macOS和Linux系统。

## 文件说明

- `snake_game_cross_platform.cpp` - 跨平台版本（支持Windows、macOS、Linux）
- `Makefile` - 编译配置文件
- `README.md` - 说明文档

## 游戏特性

- 🐍 经典贪食蛇玩法
- 🎮 键盘控制（WASD或方向键）
- 🍎 随机生成食物
- 💥 碰撞检测（边界和自身）
- 🏆 分数统计
- 🖥️ 控制台界面

## 编译和运行

### 方法1：使用Makefile（推荐）

```bash
# 编译游戏
make

# 编译并运行
make run

# 清理编译文件
make clean
```

### 方法2：手动编译

```bash
# 编译游戏
g++ -std=c++11 -Wall -Wextra -O2 -o snake_game_cross_platform snake_game_cross_platform.cpp

# 运行游戏
./snake_game_cross_platform
```

### 各平台编译说明

**Windows:**
```bash
g++ -std=c++11 -Wall -Wextra -O2 -o snake_game_cross_platform.exe snake_game_cross_platform.cpp
snake_game_cross_platform.exe
```

**macOS/Linux:**
```bash
g++ -std=c++11 -Wall -Wextra -O2 -o snake_game_cross_platform snake_game_cross_platform.cpp
./snake_game_cross_platform
```

## 游戏控制

### 方向键控制（推荐）
- `↑` - 向上移动
- `↓` - 向下移动
- `←` - 向左移动
- `→` - 向右移动

### WASD键控制
- `W` 或 `w` - 向上移动
- `S` 或 `s` - 向下移动
- `A` 或 `a` - 向左移动
- `D` 或 `d` - 向右移动

### 其他控制
- `Q` 或 `q` - 退出游戏

## 游戏规则

1. 控制蛇吃食物（*符号）
2. 每吃一个食物得10分
3. 蛇会变长
4. 撞墙或撞到自己游戏结束
5. 尽可能获得高分！

## 系统要求

- C++11或更高版本的编译器
- 支持的操作系统：Windows、macOS、Linux
- 终端/控制台环境

## 技术特点

- 面向对象设计
- 跨平台兼容性
- 方向键和WASD双重控制支持
- 无外部依赖
- 简洁的代码结构
- 良好的错误处理
- 特殊键检测（方向键）

## 开发说明

这个项目展示了以下C++编程概念：

- 类和对象
- STL容器（vector）
- 条件编译（#ifdef）
- 游戏循环
- 输入处理
- 控制台操作

## 扩展建议

可以考虑添加以下功能：

- 难度等级（调整游戏速度）
- 高分记录
- 彩色界面
- 音效支持
- 更大的游戏区域
- 特殊食物（加分道具）

## 故障排除

### 编译错误
- 确保使用C++11或更高版本
- 检查编译器是否正确安装

### 运行问题
- 确保终端支持清屏操作
- 在某些终端中可能需要调整显示设置

### 输入响应问题
- 确保终端焦点在游戏窗口上
- 某些终端可能需要按回车键确认输入

## 许可证

此项目仅供学习和教育目的使用。