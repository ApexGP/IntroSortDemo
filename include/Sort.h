#ifndef SORT_H
#define SORT_H

#include <functional>
#include <stdexcept>
#include <vector>

/**
 * @brief 排序基类，实现多种排序算法
 */
class Sort
{
protected:
    std::vector<int> data;

public:
    /**
     * @brief 构造函数
     * @param arr 要排序的数组
     * @param n 数组长度
     */
    Sort(const int arr[], int n);

    /**
     * @brief 虚析构函数
     */
    virtual ~Sort() = default;

    /**
     * @brief 排序接口
     * @param reverse 是否降序排序，默认为升序
     */
    virtual void sort(bool reverse = false);

    /**
     * @brief 获取排序后的元素
     * @param index 索引
     * @return 对应位置的元素值
     * @throw std::out_of_range 当索引越界时抛出异常
     */
    int get(int index) const;

    /**
     * @brief 获取排序后的数组大小
     * @return 数组大小
     */
    size_t size() const;

protected:
    /**
     * @brief 内省排序算法
     * @param first 起始迭代器
     * @param last 结束迭代器
     * @param depth_limit 递归深度限制
     * @param reverse 是否降序
     */
    void introsort(int* first, int* last, int depth_limit, bool reverse);

    /**
     * @brief 插入排序算法
     * @param first 起始迭代器
     * @param last 结束迭代器
     * @param reverse 是否降序
     */
    void insertion_sort(int* first, int* last, bool reverse);

    /**
     * @brief 堆排序中的堆化操作
     * @param first 堆起始位置
     * @param last 堆结束位置
     * @param root 当前根节点
     * @param reverse 是否降序
     */
    void heapify(int* first, int* last, int* root, bool reverse);

    /**
     * @brief 堆排序算法
     * @param first 起始迭代器
     * @param last 结束迭代器
     * @param reverse 是否降序
     */
    void heapsort(int* first, int* last, bool reverse);

    /**
     * @brief 快速排序的分区操作
     * @param first 起始迭代器
     * @param last 结束迭代器
     * @param pivot 枢轴值
     * @param reverse 是否降序
     * @return 分区点位置
     */
    int* partition(int* first, int* last, int pivot, bool reverse);

    /**
     * @brief 三数取中选择枢轴
     * @param a 第一个元素指针
     * @param b 第二个元素指针
     * @param c 第三个元素指针
     * @param reverse 是否降序
     * @return 中值元素指针
     */
    int* median_of_three(int* a, int* b, int* c, bool reverse);
};

#endif  // SORT_H