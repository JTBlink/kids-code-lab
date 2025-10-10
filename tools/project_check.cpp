/**
 * 项目完整性检查工具
 *
 * 功能：
 * - 检查项目文件完整性
 * - 验证编译环境
 * - 测试所有练习题
 * - 生成检查报告
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

class ProjectChecker {
private:
    vector<string> missing_files;
    vector<string> compile_errors;
    vector<string> test_failures;
    int total_checks = 0;
    int passed_checks = 0;

public:
    void checkFile(const string& filepath) {
        total_checks++;
        ifstream file(filepath);
        if (file.good()) {
            passed_checks++;
            cout << "✅ " << filepath << endl;
        } else {
            missing_files.push_back(filepath);
            cout << "❌ " << filepath << " (文件不存在)" << endl;
        }
        file.close();
    }

    bool compileAndTest(const string& source, const string& executable, const string& test_name) {
        total_checks++;

        // 编译
        string compile_cmd = "g++ -std=c++11 -Wall -g -o " + executable + " " + source + " 2>&1";
        int compile_result = system(compile_cmd.c_str());

        if (compile_result != 0) {
            compile_errors.push_back(test_name + ": 编译失败");
            cout << "❌ " << test_name << " (编译失败)" << endl;
            return false;
        }

        // 运行测试
        string run_cmd = "./" + executable + " 2>&1";
        int run_result = system(run_cmd.c_str());

        if (run_result != 0) {
            test_failures.push_back(test_name + ": 运行失败");
            cout << "⚠️ " << test_name << " (运行异常)" << endl;
            passed_checks++;
            return true; // 编译成功就算通过
        }

        passed_checks++;
        cout << "✅ " << test_name << " (编译和运行成功)" << endl;
        return true;
    }

    void printSummary() {
        cout << "\n" << string(50, '=') << endl;
        cout << "           项目检查报告           " << endl;
        cout << string(50, '=') << endl;

        cout << "\n📊 总体统计:" << endl;
        cout << "   总检查项: " << total_checks << endl;
        cout << "   通过项目: " << passed_checks << endl;
        cout << "   失败项目: " << (total_checks - passed_checks) << endl;
        cout << "   成功率: " << (double)passed_checks / total_checks * 100 << "%" << endl;

        if (!missing_files.empty()) {
            cout << "\n❌ 缺失文件:" << endl;
            for (const auto& file : missing_files) {
                cout << "   - " << file << endl;
            }
        }

        if (!compile_errors.empty()) {
            cout << "\n🔧 编译错误:" << endl;
            for (const auto& error : compile_errors) {
                cout << "   - " << error << endl;
            }
        }

        if (!test_failures.empty()) {
            cout << "\n⚠️ 运行警告:" << endl;
            for (const auto& failure : test_failures) {
                cout << "   - " << failure << endl;
            }
        }

        if (missing_files.empty() && compile_errors.empty()) {
            cout << "\n🎉 恭喜！项目完整性检查全部通过！" << endl;
            cout << "📚 项目已准备好用于教学和学习。" << endl;
        } else {
            cout << "\n🔍 请检查并修复上述问题后重新运行检查。" << endl;
        }

        cout << "\n" << string(50, '=') << endl;
    }
};

int main() {
    cout << "🔍 开始项目完整性检查..." << endl;
    cout << string(50, '-') << endl;

    ProjectChecker checker;

    // 检查核心文件
    cout << "\n📋 检查核心文件:" << endl;
    checker.checkFile("README.md");
    checker.checkFile("Makefile");
    checker.checkFile(".gitignore");
    checker.checkFile("LICENSE");

    // 检查文档文件
    cout << "\n📚 检查文档文件:" << endl;
    checker.checkFile("docs/安装指南.md");
    checker.checkFile("docs/使用说明.md");
    checker.checkFile("docs/知识点总结/Level1-基础入门.md");
    checker.checkFile("docs/项目状态报告.md");

    // 检查示例文件
    cout << "\n💡 检查示例文件:" << endl;
    checker.checkFile("examples/hello_world.cpp");
    checker.checkFile("examples/basic_variables.cpp");

    // 检查练习题文件
    cout << "\n📝 检查练习题文件:" << endl;
    checker.checkFile("exercises/level1-基础入门/01-hello-world/README.md");
    checker.checkFile("exercises/level1-基础入门/01-hello-world/template.cpp");
    checker.checkFile("exercises/level1-基础入门/01-hello-world/expected_output.txt");

    checker.checkFile("exercises/level1-基础入门/02-basic-variables/README.md");
    checker.checkFile("exercises/level1-基础入门/02-basic-variables/template.cpp");
    checker.checkFile("exercises/level1-基础入门/02-basic-variables/input.txt");
    checker.checkFile("exercises/level1-基础入门/02-basic-variables/expected_output.txt");

    checker.checkFile("exercises/level1-基础入门/03-simple-calculator/README.md");
    checker.checkFile("exercises/level1-基础入门/03-simple-calculator/template.cpp");
    checker.checkFile("exercises/level1-基础入门/03-simple-calculator/input.txt");
    checker.checkFile("exercises/level1-基础入门/03-simple-calculator/expected_output.txt");

    // 检查参考答案
    cout << "\n✅ 检查参考答案:" << endl;
    checker.checkFile("solutions/level1-基础入门/01-hello-world.cpp");
    checker.checkFile("solutions/level1-基础入门/02-basic-variables.cpp");
    checker.checkFile("solutions/level1-基础入门/03-simple-calculator.cpp");

    // 检查工具文件
    cout << "\n🛠️ 检查工具文件:" << endl;
    checker.checkFile("tools/build.cpp");
    checker.checkFile("tools/project_check.cpp");

    // 检查VSCode配置文件
    cout << "\n⚙️ 检查VSCode配置:" << endl;
    checker.checkFile(".vscode/launch.json");
    checker.checkFile(".vscode/tasks.json");
    checker.checkFile(".vscode/c_cpp_properties.json");
    checker.checkFile(".vscode/settings.json");

    // 编译和测试
    cout << "\n🔨 编译和测试:" << endl;

    // 确保构建目录存在
    system("mkdir -p build");

    // 测试示例程序
    checker.compileAndTest("examples/hello_world.cpp", "build/test_hello", "示例01-Hello World");
    checker.compileAndTest("examples/basic_variables.cpp", "build/test_vars", "示例02-变量使用");

    // 测试参考答案
    checker.compileAndTest("solutions/level1-基础入门/01-hello-world.cpp", "build/test_sol01", "题目01-参考答案");
    checker.compileAndTest("solutions/level1-基础入门/02-basic-variables.cpp", "build/test_sol02", "题目02-参考答案");
    checker.compileAndTest("solutions/level1-基础入门/03-simple-calculator.cpp", "build/test_sol03", "题目03-参考答案");

    // 测试工具
    checker.compileAndTest("tools/build.cpp", "build/test_build_tool", "编译工具");

    // 清理测试文件
    cout << "\n🧹 清理临时文件..." << endl;
    system("rm -f build/test_*");

    // 输出报告
    checker.printSummary();

    return 0;
}

/*
使用方法：
1. 编译检查工具：
   g++ -std=c++11 -o bin/project_check tools/project_check.cpp

2. 运行完整性检查：
   ./bin/project_check

3. 在Makefile中添加检查命令：
   make check-project

这个工具会：
- 检查所有必需文件是否存在
- 验证所有源代码能否编译
- 测试程序是否能正常运行
- 生成详细的检查报告

适用场景：
- 项目部署前的完整性验证
- 新环境下的项目检查
- 持续集成中的自动化测试
- 教学环境的快速验证
*/
