#include "../include/Sort.h"

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>

Sort::Sort(const int arr[], int n) : data(arr, arr + n) {}

void Sort::sort(bool reverse)
{
    if (data.empty()) return;

    // 使用内省排序而不是直接调用std::sort
    introsort(data.data(), data.data() + data.size(),
              2 * static_cast<int>(log2(data.size() > 0 ? data.size() : 1)), reverse);
}

int Sort::get(int index) const
{
    if (index >= 0 && index < static_cast<int>(data.size())) {
        return data[index];
    }
    throw std::out_of_range("索引超出范围");
}

size_t Sort::size() const
{
    return data.size();
}

void Sort::introsort(int* first, int* last, int depth_limit, bool reverse)
{
    const int size = static_cast<int>(last - first);

    // 处理小数组或空数组
    if (size <= 1) return;

    // 使用插入排序处理小数组
    if (size <= 16) {
        insertion_sort(first, last, reverse);
        return;
    }

    // 深度限制达到时切换到堆排序
    if (depth_limit == 0) {
        heapsort(first, last, reverse);
        return;
    }

    // 使用三数取中法选择枢轴
    int* mid = first + size / 2;
    int* pivot = median_of_three(first, mid, last - 1, reverse);

    // 分区
    int pvt = *pivot;
    std::swap(*pivot, *(last - 1));  // 将枢轴移到末尾

    // 高效分区实现
    int* partition_point = partition(first, last - 1, pvt, reverse);
    std::swap(*partition_point, *(last - 1));  // 恢复枢轴位置

    // 递归排序子区间
    --depth_limit;
    introsort(first, partition_point, depth_limit, reverse);
    introsort(partition_point + 1, last, depth_limit, reverse);
}

void Sort::insertion_sort(int* first, int* last, bool reverse)
{
    if (first == last) return;

    // 高效插入排序实现
    if (reverse) {
        for (int* i = first + 1; i < last; ++i) {
            int key = *i;
            int* j = i - 1;
            while (j >= first && *j < key) {
                *(j + 1) = *j;
                --j;
            }
            *(j + 1) = key;
        }
    } else {
        for (int* i = first + 1; i < last; ++i) {
            int key = *i;
            int* j = i - 1;
            while (j >= first && *j > key) {
                *(j + 1) = *j;
                --j;
            }
            *(j + 1) = key;
        }
    }
}

void Sort::heapify(int* first, int* last, int* root, bool reverse)
{
    const int heap_size = static_cast<int>(last - first);
    const int root_idx = static_cast<int>(root - first);

    int largest = root_idx;
    const int left = 2 * root_idx + 1;
    const int right = 2 * root_idx + 2;

    // 直接比较代替使用比较器，减少函数调用开销
    if (reverse) {
        if (left < heap_size && *(first + left) < *(first + largest)) {
            largest = left;
        }
        if (right < heap_size && *(first + right) < *(first + largest)) {
            largest = right;
        }
    } else {
        if (left < heap_size && *(first + left) > *(first + largest)) {
            largest = left;
        }
        if (right < heap_size && *(first + right) > *(first + largest)) {
            largest = right;
        }
    }

    if (largest != root_idx) {
        std::swap(*(first + root_idx), *(first + largest));
        // 迭代而不是递归，减少函数调用开销
        int current = largest;
        while (true) {
            const int l = 2 * current + 1;
            const int r = 2 * current + 2;
            int next = current;

            if (reverse) {
                if (l < heap_size && *(first + l) < *(first + next)) {
                    next = l;
                }
                if (r < heap_size && *(first + r) < *(first + next)) {
                    next = r;
                }
            } else {
                if (l < heap_size && *(first + l) > *(first + next)) {
                    next = l;
                }
                if (r < heap_size && *(first + r) > *(first + next)) {
                    next = r;
                }
            }

            if (next == current) break;

            std::swap(*(first + current), *(first + next));
            current = next;
        }
    }
}

void Sort::heapsort(int* first, int* last, bool reverse)
{
    const int size = static_cast<int>(last - first);

    // 构建堆
    for (int i = size / 2 - 1; i >= 0; --i) {
        heapify(first, last, first + i, reverse);
    }

    // 一个个从堆顶取出元素
    for (int i = size - 1; i > 0; --i) {
        std::swap(*first, *(first + i));
        heapify(first, first + i, first, reverse);
    }
}

int* Sort::partition(int* first, int* last, int pivot, bool reverse)
{
    int* i = first;

    // 高效分区实现
    if (reverse) {
        for (int* j = first; j < last; ++j) {
            if (*j > pivot) {
                std::swap(*i, *j);
                ++i;
            }
        }
    } else {
        for (int* j = first; j < last; ++j) {
            if (*j < pivot) {
                std::swap(*i, *j);
                ++i;
            }
        }
    }

    return i;
}

int* Sort::median_of_three(int* a, int* b, int* c, bool reverse)
{
    // 直接比较代替使用比较器，减少函数调用开销
    if (reverse) {
        if (*a > *b) {
            if (*b > *c)
                return b;  // a > b > c
            else if (*a > *c)
                return c;  // a > c >= b
            else
                return a;  // c >= a > b
        } else {
            if (*a > *c)
                return a;  // b >= a > c
            else if (*b > *c)
                return c;  // b > c >= a
            else
                return b;  // c >= b >= a
        }
    } else {
        if (*a < *b) {
            if (*b < *c)
                return b;  // a < b < c
            else if (*a < *c)
                return c;  // a < c <= b
            else
                return a;  // c <= a < b
        } else {
            if (*a < *c)
                return a;  // b <= a < c
            else if (*b < *c)
                return c;  // b < c <= a
            else
                return b;  // c <= b <= a
        }
    }
}