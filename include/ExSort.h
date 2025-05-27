#ifndef EXSORT_H
#define EXSORT_H

#include "Sort.h"

/**
 * @brief 扩展排序类，提供更友好的排序接口
 */
class ExSort : public Sort
{
public:
    /**
     * @brief 构造函数
     * @param arr 要排序的数组
     * @param n 数组长度
     */
    ExSort(const int arr[], int n);

    /**
     * @brief 虚析构函数
     */
    virtual ~ExSort() = default;

    /**
     * @brief 扩展排序接口
     * @param order 排序方向：0表示升序，非0表示降序
     */
    void exsort(int order);
};

#endif  // EXSORT_H