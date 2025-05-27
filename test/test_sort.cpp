#include <algorithm>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#include "../include/ExSort.h"
#include "../include/Sort.h"

/**
 * @brief 验证数组是否已排序
 * 
 * @param arr 要验证的数组
 * @param n 数组大小
 * @param reverse 是否为降序
 * @return true 已正确排序
 * @return false 未正确排序
 */
bool isSorted(const int arr[], int n, bool reverse = false)
{
    if (n <= 1) return true;

    for (int i = 1; i < n; ++i) {
        if (reverse) {
            // 降序验证
            if (arr[i - 1] < arr[i]) return false;
        } else {
            // 升序验证
            if (arr[i - 1] > arr[i]) return false;
        }
    }
    return true;
}

/**
 * @brief 测试排序正确性
 * 
 * @param size 测试数组大小
 * @param seed 随机种子
 */
void testSortCorrectness(int size, unsigned seed)
{
    std::cout << "===== 测试排序正确性 (大小=" << size << ") =====" << std::endl;

    // 生成随机数组
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis(0, size * 20);

    int* arr = new int[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }

    // 测试Sort类升序排序
    Sort s1(arr, size);
    s1.sort(false);

    bool sortedAsc = true;
    for (int i = 1; i < size; ++i) {
        if (s1.get(i - 1) > s1.get(i)) {
            sortedAsc = false;
            break;
        }
    }

    std::cout << "Sort类升序排序: " << (sortedAsc ? "正确" : "错误") << std::endl;
    assert(sortedAsc);

    // 测试Sort类降序排序
    Sort s2(arr, size);
    s2.sort(true);

    bool sortedDesc = true;
    for (int i = 1; i < size; ++i) {
        if (s2.get(i - 1) < s2.get(i)) {
            sortedDesc = false;
            break;
        }
    }

    std::cout << "Sort类降序排序: " << (sortedDesc ? "正确" : "错误") << std::endl;
    assert(sortedDesc);

    // 测试ExSort类升序排序
    ExSort e1(arr, size);
    e1.exsort(0);

    sortedAsc = true;
    for (int i = 1; i < size; ++i) {
        if (e1.get(i - 1) > e1.get(i)) {
            sortedAsc = false;
            break;
        }
    }

    std::cout << "ExSort类升序排序: " << (sortedAsc ? "正确" : "错误") << std::endl;
    assert(sortedAsc);

    // 测试ExSort类降序排序
    ExSort e2(arr, size);
    e2.exsort(1);

    sortedDesc = true;
    for (int i = 1; i < size; ++i) {
        if (e2.get(i - 1) < e2.get(i)) {
            sortedDesc = false;
            break;
        }
    }

    std::cout << "ExSort类降序排序: " << (sortedDesc ? "正确" : "错误") << std::endl;
    assert(sortedDesc);

    delete[] arr;
}

/**
 * @brief 测试特殊情况
 */
void testSpecialCases()
{
    std::cout << "\n===== 测试特殊情况 =====" << std::endl;

    // 测试空数组
    int emptyArr[] = {};
    Sort s0(emptyArr, 0);
    s0.sort();
    std::cout << "空数组测试: 通过" << std::endl;

    // 测试单元素数组
    int singleArr[] = {42};
    Sort s1(singleArr, 1);
    s1.sort();
    assert(s1.get(0) == 42);
    std::cout << "单元素数组测试: 通过" << std::endl;

    // 测试已排序数组
    int sortedArr[] = {1, 2, 3, 4, 5};
    Sort s2(sortedArr, 5);
    s2.sort();
    bool stillSorted = true;
    for (int i = 0; i < 5; ++i) {
        if (s2.get(i) != i + 1) {
            stillSorted = false;
            break;
        }
    }
    assert(stillSorted);
    std::cout << "已排序数组测试: 通过" << std::endl;

    // 测试逆序数组
    int reversedArr[] = {5, 4, 3, 2, 1};
    Sort s3(reversedArr, 5);
    s3.sort();
    bool correctlySorted = true;
    for (int i = 0; i < 5; ++i) {
        if (s3.get(i) != i + 1) {
            correctlySorted = false;
            break;
        }
    }
    assert(correctlySorted);
    std::cout << "逆序数组测试: 通过" << std::endl;

    // 测试全相等元素数组
    int equalArr[] = {7, 7, 7, 7, 7};
    Sort s4(equalArr, 5);
    s4.sort();
    bool allEqual = true;
    for (int i = 0; i < 5; ++i) {
        if (s4.get(i) != 7) {
            allEqual = false;
            break;
        }
    }
    assert(allEqual);
    std::cout << "全相等元素数组测试: 通过" << std::endl;
}

/**
 * @brief 测试性能
 */
void testPerformance()
{
    std::cout << "\n===== 性能测试 =====" << std::endl;

    std::vector<int> sizes = {1000, 10000, 100000};
    unsigned seed = 42;
    std::mt19937 gen(seed);

    std::cout << std::setw(10) << "大小" << std::setw(15) << "Sort升序(ms)" << std::setw(15)
              << "Sort降序(ms)" << std::setw(15) << "ExSort升序(ms)" << std::setw(15)
              << "ExSort降序(ms)" << std::endl;

    for (int size : sizes) {
        // 生成随机数组
        std::uniform_int_distribution<> dis(0, size * 20);
        int* arr = new int[size];
        for (int i = 0; i < size; ++i) {
            arr[i] = dis(gen);
        }

        // 测试Sort升序
        auto start = std::chrono::high_resolution_clock::now();
        Sort s1(arr, size);
        s1.sort(false);
        auto end = std::chrono::high_resolution_clock::now();
        auto durationSort1 =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // 测试Sort降序
        start = std::chrono::high_resolution_clock::now();
        Sort s2(arr, size);
        s2.sort(true);
        end = std::chrono::high_resolution_clock::now();
        auto durationSort2 =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // 测试ExSort升序
        start = std::chrono::high_resolution_clock::now();
        ExSort e1(arr, size);
        e1.exsort(0);
        end = std::chrono::high_resolution_clock::now();
        auto durationExSort1 =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // 测试ExSort降序
        start = std::chrono::high_resolution_clock::now();
        ExSort e2(arr, size);
        e2.exsort(1);
        end = std::chrono::high_resolution_clock::now();
        auto durationExSort2 =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << std::setw(10) << size << std::setw(15) << durationSort1 << std::setw(15)
                  << durationSort2 << std::setw(15) << durationExSort1 << std::setw(15)
                  << durationExSort2 << std::endl;

        delete[] arr;
    }
}

int main()
{
    std::cout << "开始排序算法测试...\n" << std::endl;

    // 使用固定种子以便重现测试结果
    unsigned seed = 42;

    // 测试正确性
    testSortCorrectness(100, seed);
    testSortCorrectness(1000, seed);

    // 测试特殊情况
    testSpecialCases();

    // 测试性能
    testPerformance();

    std::cout << "\n所有测试通过！" << std::endl;

    return 0;
}