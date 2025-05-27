#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "../include/ExSort.h"
#include "../include/Sort.h"

/**
 * @brief 显示排序结果
 * 
 * @param s 排序对象指针
 * @param partial 是否部分显示
 * @param n 数组大小
 */
void disp(Sort* s, int partial, int n)
{
    if (partial == 0) {
        // 完整显示排序结果
        for (int i = 0; i < n; i++) {
            std::cout << s->get(i) << " ";
        }
        std::cout << std::endl;
    } else {
        // 随机显示不超过20个元素
        int nprint = (n > 20) ? 20 : n;
        for (int i = 0; i < nprint; i++) {
            std::cout << s->get(rand() % n) << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * @brief 主函数
 * 
 * @param argc 命令行参数个数
 * @param argv 命令行参数数组
 * @return int 程序退出状态
 */
int main(int argc, char** argv)
{
    // 检查命令行参数
    if (argc < 4) {
        std::cerr << "用法: " << argv[0] << " <数组大小> <显示模式> <随机种子>" << std::endl;
        std::cerr << "  数组大小: 要排序的整数数量" << std::endl;
        std::cerr << "  显示模式: 0=完整显示, 1=随机显示部分元素" << std::endl;
        std::cerr << "  随机种子: 用于生成随机数的种子" << std::endl;
        return 1;
    }

    // 解析命令行参数
    int n = std::stoi(argv[1]);
    int partial_disp = std::stoi(argv[2]);
    int seed = std::stoi(argv[3]);

    // 设置随机数种子
    srand(seed);

    // 生成随机数组
    int* list = new int[n];
    for (int i = 0; i < n; i++) {
        list[i] = rand() % (n * 20);
    }

    // 使用Sort类测试升序排序
    std::cout << "===== 测试Sort类(升序) =====" << std::endl;
    Sort s0(list, n);
    std::cout << "排序前: ";
    disp(&s0, partial_disp, n);

    s0.sort();  // 升序排序

    std::cout << "排序后: ";
    disp(&s0, partial_disp, n);

    // 使用ExSort类测试降序排序
    std::cout << "\n===== 测试ExSort类(降序) =====" << std::endl;
    ExSort s1(list, n);
    std::cout << "排序前: ";
    disp(&s1, partial_disp, n);

    s1.exsort(1);  // 降序排序

    std::cout << "排序后: ";
    disp(&s1, partial_disp, n);

    // 释放内存
    delete[] list;

    return 0;
}