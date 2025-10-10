/**
 * 变量和数据类型示例
 * 适合：小学生入门
 * 学习目标：了解基本数据类型和变量的使用
 */

#include <iostream>
using namespace std;

int main() {
    // 整数类型
    int age = 12;                    // 年龄
    int score = 95;                  // 分数
    
    // 小数类型
    double height = 1.45;            // 身高(米)
    double weight = 35.5;            // 体重(公斤)
    
    // 字符类型
    char grade = 'A';                // 等级
    
    // 字符串类型
    string name = "小明";            // 姓名
    string school = "阳光小学";      // 学校
    
    // 布尔类型
    bool isStudent = true;           // 是否是学生
    
    // 输出个人信息
    cout << "=== 学生信息卡 ===" << endl;
    cout << "姓名: " << name << endl;
    cout << "年龄: " << age << "岁" << endl;
    cout << "身高: " << height << "米" << endl;
    cout << "体重: " << weight << "公斤" << endl;
    cout << "学校: " << school << endl;
    cout << "成绩等级: " << grade << endl;
    cout << "考试分数: " << score << "分" << endl;
    
    if (isStudent) {
        cout << "身份: 在校学生" << endl;
    }
    
    // 简单计算
    double bmi = weight / (height * height);
    cout << "BMI指数: " << bmi << endl;
    
    return 0;
}

/*
数据类型说明：
1. int - 整数，如年龄、分数
2. double - 小数，如身高、体重
3. char - 单个字符，如等级
4. string - 字符串，如姓名
5. bool - 布尔值，true或false

变量命名规则：
1. 使用有意义的名字
2. 第一个字符必须是字母或下划线
3. 区分大小写
4. 不能使用C++关键字
*/
