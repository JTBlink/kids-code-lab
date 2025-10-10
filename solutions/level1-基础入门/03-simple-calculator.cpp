/**
 * 题目03：我的小计算器 - 参考答案
 * 
 * 知识点：
 * - 条件判断语句 (if-else)
 * - 字符变量的使用
 * - 数学运算符
 * - 错误处理（除零检查）
 */

#include <iostream>
using namespace std;

int main() {
    // 声明变量
    double num1, num2, result;
    char operator_symbol;
    
    // 读取用户输入
    cout << "请输入第一个数字: ";
    cin >> num1;
    
    cout << "请输入运算符(+,-,*,/): ";
    cin >> operator_symbol;
    
    cout << "请输入第二个数字: ";
    cin >> num2;
    
    // 根据运算符进行计算
    if (operator_symbol == '+') {
        result = num1 + num2;
        cout << "计算结果: " << num1 << " + " << num2 << " = " << result << endl;
    }
    else if (operator_symbol == '-') {
        result = num1 - num2;
        cout << "计算结果: " << num1 << " - " << num2 << " = " << result << endl;
    }
    else if (operator_symbol == '*') {
        result = num1 * num2;
        cout << "计算结果: " << num1 << " * " << num2 << " = " << result << endl;
    }
    else if (operator_symbol == '/') {
        if (num2 != 0) {
            result = num1 / num2;
            cout << "计算结果: " << num1 << " / " << num2 << " = " << result << endl;
        } else {
            cout << "错误：除数不能为0" << endl;
        }
    }
    else {
        cout << "错误：不支持的运算符 " << operator_symbol << endl;
    }
    
    return 0;
}

/*
=== 解题思路 ===

1. 变量设计：
   - double num1, num2：存储两个操作数，使用double支持小数运算
   - char operator_symbol：存储运算符，单个字符
   - double result：存储计算结果

2. 输入处理：
   - 按顺序读取数字、运算符、数字
   - 使用清晰的提示信息

3. 条件判断：
   - 使用if-else if结构判断运算符类型
   - 每个分支处理一种运算

4. 特殊情况处理：
   - 除法运算前检查除数是否为0
   - 对无效运算符给出错误提示

=== 知识拓展 ===

1. 使用switch语句的版本：
```cpp
switch (operator_symbol) {
    case '+':
        result = num1 + num2;
        break;
    case '-':
        result = num1 - num2;
        break;
    case '*':
        result = num1 * num2;
        break;
    case '/':
        if (num2 != 0) {
            result = num1 / num2;
        } else {
            cout << "错误：除数不能为0" << endl;
            return 1; // 错误退出
        }
        break;
    default:
        cout << "错误：不支持的运算符" << endl;
        return 1;
}
cout << "计算结果: " << num1 << " " << operator_symbol << " " << num2 << " = " << result << endl;
```

2. 函数版本：
```cpp
double calculate(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b != 0) return a / b;
            else {
                cout << "错误：除数不能为0" << endl;
                return 0;
            }
        default:
            cout << "错误：不支持的运算符" << endl;
            return 0;
    }
}
```

3. 循环计算版本：
```cpp
int main() {
    char continue_calc = 'y';
    
    while (continue_calc == 'y' || continue_calc == 'Y') {
        // 执行一次计算
        // ...
        
        cout << "是否继续计算？(y/n): ";
        cin >> continue_calc;
    }
    
    cout << "感谢使用计算器！" << endl;
    return 0;
}
```

=== 常见错误解决 ===

1. 字符比较错误：
   错误：if (operator_symbol = '+')  // 使用了赋值而不是比较
   正确：if (operator_symbol == '+') // 使用比较运算符

2. 整数除法问题：
   错误：int result = 10 / 3;  // 结果为3，丢失小数部分
   正确：double result = 10.0 / 3.0;  // 结果为3.33333...

3. 输入缓冲区问题：
   如果程序行为异常，可能需要清空输入缓冲区：
   cin.ignore();  // 忽略换行符

=== 扩展练习 ===

1. 添加更多运算：
   - 求余运算 (%)
   - 乘方运算 (pow函数)
   - 开方运算 (sqrt函数)

2. 美化界面：
   - 添加欢迎信息
   - 使用表格形式显示结果
   - 添加分隔线

3. 输入验证：
   - 检查数字输入的有效性
   - 处理非数字输入的情况

示例扩展版本：
```cpp
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    cout << "=== 欢迎使用小计算器 ===" << endl;
    cout << "支持运算：+, -, *, /, %, ^(乘方)" << endl;
    cout << "=========================" << endl;
    
    double num1, num2, result;
    char op;
    
    cout << "请输入第一个数字: ";
    cin >> num1;
    
    cout << "请输入运算符: ";
    cin >> op;
    
    cout << "请输入第二个数字: ";
    cin >> num2;
    
    cout << "\n=== 计算结果 ===" << endl;
    cout << "算式: " << num1 << " " << op << " " << num2 << endl;
    
    switch (op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                cout << "错误: 除数不能为0!" << endl;
                return 1;
            }
            break;
        case '%':
            if (num2 != 0) {
                result = fmod(num1, num2);  // 浮点数取余
            } else {
                cout << "错误: 除数不能为0!" << endl;
                return 1;
            }
            break;
        case '^':
            result = pow(num1, num2);
            break;
        default:
            cout << "错误: 不支持的运算符!" << endl;
            return 1;
    }
    
    cout << "结果: " << fixed << setprecision(2) << result << endl;
    cout << "================" << endl;
    
    return 0;
}
```
*/
