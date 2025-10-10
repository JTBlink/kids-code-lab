/**
 * 题目01：我的第一个程序 - 参考答案
 * 
 * 知识点：
 * - C++程序基本结构
 * - 输出语句cout的使用
 * - 头文件包含和命名空间
 */

#include <iostream>
using namespace std;

int main() {
    // 方法一：逐行输出（推荐新手使用）
    cout << "Hello, World!" << endl;
    cout << "我是小程序员！" << endl;
    cout << "今天开始学习C++编程了！" << endl;
    
    return 0;
}

/*
=== 解题思路 ===

1. 程序结构分析：
   - #include <iostream>：包含输入输出流库
   - using namespace std：使用标准命名空间
   - int main()：主函数，程序入口点
   - return 0：表示程序正常结束

2. 输出语句：
   - cout：标准输出流对象
   - <<：流插入运算符
   - endl：换行符并刷新缓冲区

3. 字符串处理：
   - 使用双引号包围文本
   - 支持中文字符
   - 每个输出语句以分号结尾

=== 其他解法 ===

// 方法二：连续输出
cout << "Hello, World!" << endl
     << "我是小程序员！" << endl
     << "今天开始学习C++编程了！" << endl;

// 方法三：使用\n换行
cout << "Hello, World!\n我是小程序员！\n今天开始学习C++编程了！\n";

=== 常见错误及解决 ===

1. 编译错误：
   错误：忘记包含头文件
   解决：添加 #include <iostream>

2. 链接错误：
   错误：找不到main函数
   解决：确保有int main()函数

3. 运行时错误：
   错误：输出乱码
   解决：确认编译器支持UTF-8编码

=== 知识拓展 ===

1. 为什么要写return 0？
   - 0表示程序正常结束
   - 非0值表示程序异常结束
   - 在main函数中可以省略，编译器会自动添加

2. cout和printf的区别：
   - cout是C++的输出方式，类型安全
   - printf是C语言的输出方式，需要格式控制

3. endl和\n的区别：
   - endl会刷新输出缓冲区，\n不会
   - 大量输出时，\n效率更高
*/
