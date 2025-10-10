/**
 * 题目02：自我介绍小程序 - 参考答案
 * 
 * 知识点：
 * - 变量声明和使用
 * - 基本输入输出操作
 * - 数据类型（int, string, double）
 * - 简单数学运算
 */

#include <iostream>
#include <string>
using namespace std;

int main() {
    // 声明变量来存储用户信息
    string name;
    int age;
    double height;
    
    // 读取用户输入
    cout << "请输入你的姓名: ";
    cin >> name;
    
    cout << "请输入你的年龄: ";
    cin >> age;
    
    cout << "请输入你的身高(米): ";
    cin >> height;
    
    // 计算出生年份
    int birthYear = 2024 - age;
    
    // 格式化输出
    cout << "=== 自我介绍 ===" << endl;
    cout << "大家好！我叫" << name << endl;
    cout << "我今年" << age << "岁了" << endl;
    cout << "我的身高是" << height << "米" << endl;
    cout << "我是在" << birthYear << "年出生的" << endl;
    cout << "很高兴认识大家！" << endl;
    
    return 0;
}

/*
=== 解题思路 ===

1. 变量设计：
   - string name：存储姓名，可以包含中文字符
   - int age：存储年龄，整数类型
   - double height：存储身高，双精度浮点数

2. 输入处理：
   - 使用cin >>读取基本数据类型
   - 每次输入前给出清晰的提示

3. 数据计算：
   - 出生年份 = 当前年份 - 年龄
   - 简单的减法运算

4. 输出格式化：
   - 使用cout <<连接文本和变量
   - 注意中文字符的正确显示

=== 知识拓展 ===

1. 其他输入方式：
// 如果姓名包含空格，可以用：
getline(cin, name);

2. 数据类型选择：
// 更精确的身高存储
float height;  // 单精度，占用空间更小
double height; // 双精度，精度更高

3. 常量的使用：
const int CURRENT_YEAR = 2024;
int birthYear = CURRENT_YEAR - age;

=== 常见问题解决 ===

1. 中文输出乱码：
   - 确保编译器支持UTF-8编码
   - 在Windows上可能需要设置控制台编码

2. 输入缓冲区问题：
   // 如果混合使用cin和getline，可能需要清空缓冲区
   cin.ignore(); // 忽略换行符
   getline(cin, name);

3. 小数精度显示：
   #include <iomanip>
   cout << fixed << setprecision(2) << height; // 显示2位小数

=== 变式练习 ===

1. 添加更多信息：
   - 体重（计算BMI）
   - 最喜欢的学科
   - 家乡城市

2. 增加数据验证：
   - 检查年龄是否合理（0-150）
   - 检查身高是否合理（0.5-3.0米）

3. 美化输出：
   - 添加边框装饰
   - 使用不同的分隔符
   - 添加个性化问候语

示例扩展版本：
```cpp
int main() {
    string name, hobby;
    int age, score;
    double height, weight;
    
    cout << "=== 欢迎来到自我介绍程序 ===" << endl;
    
    cout << "请输入你的姓名: ";
    cin >> name;
    
    cout << "请输入你的年龄: ";
    cin >> age;
    
    cout << "请输入你的身高(米): ";
    cin >> height;
    
    cout << "请输入你的体重(公斤): ";
    cin >> weight;
    
    cout << "请输入你最喜欢的学科: ";
    cin >> hobby;
    
    // 计算BMI和出生年份
    double bmi = weight / (height * height);
    int birthYear = 2024 - age;
    
    cout << "\n=== 个人档案 ===" << endl;
    cout << "┌─────────────────────────┐" << endl;
    cout << "│ 姓名: " << name << "                │" << endl;
    cout << "│ 年龄: " << age << "岁               │" << endl;
    cout << "│ 身高: " << height << "米            │" << endl;
    cout << "│ 体重: " << weight << "公斤          │" << endl;
    cout << "│ BMI:  " << bmi << "              │" << endl;
    cout << "│ 出生: " << birthYear << "年         │" << endl;
    cout << "│ 爱好: " << hobby << "              │" << endl;
    cout << "└─────────────────────────┘" << endl;
    
    return 0;
}
```
*/
