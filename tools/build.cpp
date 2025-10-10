/**
 * 简单的编译和测试工具
 * 适合中小学生使用的C++练习题目编译器
 */

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

void showUsage() {
    cout << "=== C++练习题编译工具 ===" << endl;
    cout << "使用方法：" << endl;
    cout << "1. 编译单个文件: g++ -o 程序名 源文件.cpp" << endl;
    cout << "2. 编译并运行: g++ -o 程序名 源文件.cpp && ./程序名" << endl;
    cout << "3. 测试程序: g++ -o 程序名 源文件.cpp && ./程序名 < input.txt" << endl;
    cout << endl;
    cout << "示例：" << endl;
    cout << "g++ -o hello 01-hello-world.cpp" << endl;
    cout << "./hello" << endl;
    cout << endl;
    cout << "常用编译选项：" << endl;
    cout << "-std=c++11  : 使用C++11标准" << endl;
    cout << "-Wall       : 显示所有警告" << endl;
    cout << "-g          : 包含调试信息" << endl;
    cout << "-O2         : 优化代码" << endl;
}

int main(int argc, char* argv[]) {
    cout << "=== 欢迎使用C++练习题编译工具 ===" << endl;
    
    if (argc < 2) {
        showUsage();
        return 0;
    }
    
    string command = argv[1];
    
    if (command == "help" || command == "--help" || command == "-h") {
        showUsage();
    }
    else if (command == "compile") {
        if (argc < 3) {
            cout << "错误：请指定要编译的文件" << endl;
            cout << "用法: ./build compile 文件名.cpp" << endl;
            return 1;
        }
        
        string filename = argv[2];
        string outputName = filename.substr(0, filename.find('.'));
        string compileCmd = "g++ -std=c++11 -Wall -o " + outputName + " " + filename;
        
        cout << "正在编译: " << filename << endl;
        cout << "命令: " << compileCmd << endl;
        
        int result = system(compileCmd.c_str());
        if (result == 0) {
            cout << "✅ 编译成功！生成可执行文件: " << outputName << endl;
            cout << "运行程序: ./" << outputName << endl;
        } else {
            cout << "❌ 编译失败，请检查代码错误" << endl;
        }
    }
    else if (command == "test") {
        if (argc < 3) {
            cout << "错误：请指定要测试的文件" << endl;
            cout << "用法: ./build test 文件名.cpp" << endl;
            return 1;
        }
        
        string filename = argv[2];
        string outputName = filename.substr(0, filename.find('.'));
        string compileCmd = "g++ -std=c++11 -Wall -o " + outputName + " " + filename;
        string runCmd = "./" + outputName;
        
        cout << "正在编译和测试: " << filename << endl;
        
        // 编译
        int compileResult = system(compileCmd.c_str());
        if (compileResult != 0) {
            cout << "❌ 编译失败" << endl;
            return 1;
        }
        
        cout << "✅ 编译成功，开始运行程序..." << endl;
        cout << "===================" << endl;
        
        // 运行
        int runResult = system(runCmd.c_str());
        cout << "===================" << endl;
        
        if (runResult == 0) {
            cout << "✅ 程序运行完成" << endl;
        } else {
            cout << "⚠️ 程序运行结束（返回码: " << runResult << "）" << endl;
        }
    }
    else {
        cout << "未知命令: " << command << endl;
        showUsage();
    }
    
    return 0;
}

/*
使用说明：

1. 编译这个工具：
   g++ -o build build.cpp

2. 使用工具编译练习题：
   ./build compile hello.cpp

3. 使用工具测试练习题：
   ./build test hello.cpp

4. 查看帮助：
   ./build help

这个工具简化了编译过程，让学生专注于编程逻辑而不是复杂的编译命令。
*/
