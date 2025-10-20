/*
 * 跨平台贪吃蛇游戏 - 适合初学者学习的C++项目
 *
 * 这个程序演示了以下C++概念：
 * 1. 类和对象的设计
 * 2. 条件编译（跨平台兼容性）
 * 3. STL容器的使用（vector）
 * 4. 游戏循环的实现
 * 5. 用户输入处理
 * 6. 控制台图形绘制
 */

// 标准库头文件
#include <iostream>    // 用于输入输出操作（cout, cin等）
#include <vector>      // 用于动态数组，存储蛇的身体节点
#include <cstdlib>     // 用于随机数生成（rand, srand）
#include <ctime>       // 用于获取当前时间，作为随机数种子
#include <chrono>      // 用于精确的时间控制
#include <thread>      // 用于线程休眠，控制游戏速度

// 条件编译：根据不同操作系统包含不同的头文件
#ifdef _WIN32
    // Windows系统专用头文件
    #include <conio.h>     // 用于键盘输入检测（_kbhit, _getch）
    #include <windows.h>   // Windows API
#else
    // Unix/Linux/macOS系统专用头文件
    #include <termios.h>   // 用于终端控制
    #include <unistd.h>    // Unix标准定义
    #include <fcntl.h>     // 文件控制操作
#endif

using namespace std;  // 使用标准命名空间，避免每次写std::

/*
 * 跨平台贪吃蛇游戏类
 *
 * 这个类封装了贪吃蛇游戏的所有功能，包括：
 * - 游戏状态管理
 * - 用户输入处理
 * - 游戏逻辑计算
 * - 屏幕绘制
 */
class CrossPlatformSnakeGame {
private:
    // 游戏区域大小常量
    static const int WIDTH = 30;   // 游戏区域宽度（字符数）
    static const int HEIGHT = 20;  // 游戏区域高度（字符数）

    /*
     * Point结构体：表示游戏中的一个坐标点
     * 用于表示蛇的身体节点和食物的位置
     */
    struct Point {
        int x, y;  // x坐标和y坐标

        // 构造函数：创建一个点，默认坐标为(0,0)
        // 使用初始化列表的方式直接初始化成员变量，这是C++的最佳实践
        Point(int x = 0, int y = 0) : x(x), y(y) {}

        // 重载==操作符：用于比较两个点是否相等
        // const关键字表示这个函数不会修改对象的状态
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
    };

    // 游戏状态变量
    vector<Point> snake;    // 蛇的身体，用vector存储所有身体节点
    Point food;             // 食物的位置
    char direction;         // 当前移动方向（'w'上, 's'下, 'a'左, 'd'右）
    bool gameOver;          // 游戏是否结束的标志
    int score;              // 当前得分

#ifndef _WIN32
    // 非Windows系统需要保存原始终端设置，以便游戏结束后恢复
    struct termios oldTermios;
#endif

public:
    /*
     * 构造函数：初始化游戏状态
     * 当创建游戏对象时自动调用，设置游戏的初始状态
     */
    CrossPlatformSnakeGame() {
        // 初始化游戏状态
        gameOver = false;    // 游戏开始时未结束
        direction = 'd';     // 初始方向向右移动
        score = 0;           // 初始分数为0

        // 初始化蛇的位置（在屏幕中央创建一条长度为3的蛇）
        // 蛇头在最前面，蛇身依次向左排列
        snake.push_back(Point(WIDTH/2, HEIGHT/2));      // 蛇头
        snake.push_back(Point(WIDTH/2-1, HEIGHT/2));    // 蛇身第一节
        snake.push_back(Point(WIDTH/2-2, HEIGHT/2));    // 蛇身第二节

        // 生成第一个食物
        generateFood();

        // 初始化随机数种子，使用当前时间确保每次运行游戏食物位置都不同
        srand(time(0));

        // 设置输入模式（让程序能够实时检测键盘输入）
        setupInput();
    }

    /*
     * 析构函数：清理资源
     * 当游戏对象被销毁时自动调用，恢复终端设置
     */
    ~CrossPlatformSnakeGame() {
        restoreInput();  // 恢复终端的原始设置
    }

    /*
     * 设置输入模式
     * 在非Windows系统上，需要设置终端为非阻塞模式，
     * 这样程序就能实时检测键盘输入而不需要等待回车键
     */
    void setupInput() {
#ifndef _WIN32
        // 获取当前终端设置并保存
        tcgetattr(STDIN_FILENO, &oldTermios);

        // 创建新的终端设置
        struct termios newTermios = oldTermios;

        // 关闭规范模式和回显模式
        // ICANON: 规范模式（需要按回车才能读取输入）
        // ECHO: 回显模式（输入的字符会显示在屏幕上）
        newTermios.c_lflag &= ~(ICANON | ECHO);

        // 应用新的终端设置
        tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);

        // 设置为非阻塞模式，这样getchar()不会等待输入
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
#endif
    }

    /*
     * 恢复输入模式
     * 游戏结束时恢复终端的原始设置
     */
    void restoreInput() {
#ifndef _WIN32
        // 恢复保存的原始终端设置
        tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
#endif
    }

    /*
     * 生成食物
     * 在游戏区域内随机生成一个食物，确保食物不会出现在蛇的身体上
     */
    void generateFood() {
        do {
            // 在游戏区域内随机生成坐标
            food.x = rand() % WIDTH;   // x坐标：0到WIDTH-1
            food.y = rand() % HEIGHT;  // y坐标：0到HEIGHT-1
        } while (isSnakeBody(food));   // 如果食物位置与蛇身重叠，重新生成
    }

    /*
     * 检查指定点是否是蛇的身体
     * 参数：p - 要检查的点
     * 返回：如果点p在蛇身上返回true，否则返回false
     */
    bool isSnakeBody(const Point& p) {
        // 遍历蛇的所有身体节点
        for (const auto& segment : snake) {
            if (segment == p) return true;  // 找到匹配的节点
        }
        return false;  // 没有找到匹配的节点
    }

    /*
     * 清屏函数
     * 根据不同的操作系统使用不同的清屏命令
     */
    void clearScreen() {
#ifdef _WIN32
        system("cls");    // Windows系统使用cls命令清屏
#else
        system("clear");  // Unix/Linux/macOS系统使用clear命令清屏
#endif
    }

    /*
     * 绘制游戏画面
     * 这个函数负责在控制台上绘制整个游戏界面，包括：
     * - 游戏边界（用#字符）
     * - 蛇的身体（蛇头用O，蛇身用o）
     * - 食物（用*字符）
     * - 分数和控制说明
     */
    void draw() {
        clearScreen();  // 先清屏

        // 绘制顶部边界
        // WIDTH + 2 是因为要加上左右两个边界字符
        for (int i = 0; i < WIDTH + 2; i++) cout << "#";
        cout << endl;

        // 绘制游戏区域（逐行绘制）
        for (int y = 0; y < HEIGHT; y++) {
            cout << "#"; // 左边界

            // 绘制这一行的内容
            for (int x = 0; x < WIDTH; x++) {
                Point current(x, y);  // 当前要绘制的位置

                // 判断当前位置应该显示什么字符
                if (current == snake[0]) {
                    cout << "9";  // 蛇头用大写O表示
                } else if (isSnakeBody(current)) {
                    cout << "o"; // 蛇身用小写o表示
                } else if (current == food) {
                    cout << "*"; // 食物用星号表示
                } else {
                    cout << " "; // 空地用空格表示
                }
            }

            cout << "#" << endl; // 右边界
        }

        // 绘制底部边界
        for (int i = 0; i < WIDTH + 2; i++) cout << "#";
        cout << endl;

        // 显示游戏信息
        cout << "Score: " << score << endl;
        cout << "Controls: Arrow Keys or WASD to move, Q to quit" << endl;
    }

    /*
     * 检查是否有键盘输入
     * 这是一个跨平台的函数，用于检测是否有按键被按下
     * 返回：如果有按键返回true，否则返回false
     */
    bool kbhit() {
#ifdef _WIN32
        // Windows系统直接使用_kbhit()函数
        return _kbhit();
#else
        // 非Windows系统的实现
        int ch = getchar();
        if (ch != EOF) {
            // 如果读到了字符，把它放回输入缓冲区
            ungetc(ch, stdin);
            return true;
        }
        return false;
#endif
    }

    /*
     * 获取一个字符输入
     * 跨平台的字符输入函数
     * 返回：按下的字符
     */
    char getch() {
#ifdef _WIN32
        return _getch();   // Windows系统使用_getch()
#else
        return getchar();  // 非Windows系统使用getchar()
#endif
    }

    /*
     * 获取特殊键（如方向键）
     * 方向键在不同系统上有不同的编码方式，这个函数统一处理
     * 返回值：1=上, 2=下, 3=左, 4=右, 其他=普通字符的ASCII码
     */
    int getSpecialKey() {
#ifdef _WIN32
        // Windows系统的方向键处理
        int key = _getch();
        if (key == 0 || key == 224) { // 特殊键前缀（Windows方向键的特征）
            key = _getch();  // 读取实际的键码
            switch (key) {
                case 72: return 1; // 上箭头键
                case 80: return 2; // 下箭头键
                case 75: return 3; // 左箭头键
                case 77: return 4; // 右箭头键
            }
        }
        return key;  // 返回普通字符
#else
        // Unix/Linux/macOS系统的方向键处理
        int key = getchar();
        if (key == 27) { // ESC序列开始（Unix方向键以ESC开头）
            if (getchar() == 91) { // 检查是否为 '['
                key = getchar();  // 读取方向键的具体编码
                switch (key) {
                    case 65: return 1; // 上箭头键
                    case 66: return 2; // 下箭头键
                    case 68: return 3; // 左箭头键
                    case 67: return 4; // 右箭头键
                }
            }
        }
        return key;  // 返回普通字符
#endif
    }

    /*
     * 处理用户输入
     * 检测键盘输入并更新蛇的移动方向
     * 支持方向键和WASD键控制，Q键退出游戏
     */
    void input() {
        if (kbhit()) {  // 如果有按键输入
            int key = getSpecialKey();  // 获取按键

            // 处理方向键
            switch (key) {
                case 1: // 上箭头
                    // 防止蛇直接掉头（如果当前向下移动，不能直接向上）
                    if (direction != 's') direction = 'w';
                    break;
                case 2: // 下箭头
                    if (direction != 'w') direction = 's';
                    break;
                case 3: // 左箭头
                    if (direction != 'd') direction = 'a';
                    break;
                case 4: // 右箭头
                    if (direction != 'a') direction = 'd';
                    break;
                default:
                    // 处理普通字符键（WASD和Q）
                    char normalKey = tolower(key);  // 转换为小写
                    switch (normalKey) {
                        case 'w':  // W键向上
                            if (direction != 's') direction = 'w';
                            break;
                        case 's':  // S键向下
                            if (direction != 'w') direction = 's';
                            break;
                        case 'a':  // A键向左
                            if (direction != 'd') direction = 'a';
                            break;
                        case 'd':  // D键向右
                            if (direction != 'a') direction = 'd';
                            break;
                        case 'q':  // Q键退出游戏
                            gameOver = true;
                            break;
                    }
                    break;
            }
        }
    }

    /*
     * 游戏逻辑处理
     * 这是游戏的核心函数，处理蛇的移动、碰撞检测、食物检测等
     * 每一帧都会调用这个函数来更新游戏状态
     */
    void logic() {
        // 计算新的头部位置
        // 根据当前方向，计算蛇头的下一个位置
        Point newHead = snake[0];  // 复制当前蛇头位置

        // 根据移动方向更新蛇头坐标
        switch (direction) {
            case 'w': newHead.y--; break; // 向上移动（y坐标减小）
            case 's': newHead.y++; break; // 向下移动（y坐标增大）
            case 'a': newHead.x--; break; // 向左移动（x坐标减小）
            case 'd': newHead.x++; break; // 向右移动（x坐标增大）
        }

        // 检查边界碰撞
        // 如果蛇头移动到游戏区域外，游戏结束
        if (newHead.x < 0 || newHead.x >= WIDTH ||
            newHead.y < 0 || newHead.y >= HEIGHT) {
            gameOver = true;
            return;  // 立即返回，不继续执行后面的代码
        }

        // 检查自身碰撞
        // 如果蛇头撞到自己的身体，游戏结束
        if (isSnakeBody(newHead)) {
            gameOver = true;
            return;
        }

        // 移动蛇：在蛇头前面添加新的头部
        snake.insert(snake.begin(), newHead);

        // 检查是否吃到食物
        if (newHead == food) {
            // 吃到食物：增加分数，生成新食物
            score += 10;        // 每个食物10分
            generateFood();     // 生成新的食物
            // 注意：吃到食物时不移除蛇尾，所以蛇会变长
        } else {
            // 没吃到食物：移除蛇尾，保持蛇的长度不变
            snake.pop_back();
        }
    }

    /*
     * 运行游戏
     * 这是游戏的主循环函数，控制整个游戏的流程
     */
    void run() {
        // 显示游戏开始信息
        cout << "=== C++ Snake Game ===" << endl;
        cout << "Press any key to start..." << endl;
        getch();  // 等待用户按键开始游戏

        // 游戏主循环
        // 只要游戏没有结束，就一直循环执行以下步骤
        while (!gameOver) {
            draw();     // 1. 绘制游戏画面
            input();    // 2. 处理用户输入
            logic();    // 3. 更新游戏逻辑

            // 4. 控制游戏速度（每帧间隔150毫秒）
            // 这个延时决定了蛇移动的速度，数值越小蛇移动越快
            this_thread::sleep_for(chrono::milliseconds(200));
        }

        // 游戏结束后的处理
        clearScreen();
        cout << "=== Game Over ===" << endl;
        cout << "Final Score: " << score << endl;
        cout << "Thanks for playing! Press any key to exit..." << endl;
        getch();  // 等待用户按键退出
    }
};

/*
 * 主函数：程序入口
 * 创建一个贪吃蛇游戏对象并运行游戏
 */
int main() {
    // 创建游戏对象
    CrossPlatformSnakeGame game;

    // 运行游戏
    game.run();

    // 程序正常结束
    return 0;
}
