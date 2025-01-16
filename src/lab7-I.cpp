#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

class Sort
{
protected:
    std::vector<int> data;

public:
    Sort(int arr[], int n) : data(arr, arr + n) {}

    // 默认升序排序
    virtual void sort(bool reverse = false)
    {
        introsort(data.data(), data.data() + data.size(), 2 * static_cast<int>(log2(data.size())),
                  reverse);
    }

    int get(int index) const
    {
        if (index >= 0 && index < data.size()) {
            return data[index];
        }
        throw std::out_of_range("Index out of range");
    }

    virtual ~Sort() = default;

protected:
    void introsort(int* first, int* last, int depth_limit, bool reverse)
    {
        while (last - first > 16) {
            if (depth_limit == 0) {
                heapsort(first, last, reverse);
                return;
            }

            --depth_limit;
            int* pivot = median_of_three(first, first + (last - first) / 2, last - 1, reverse);
            pivot = partition(first, last, *pivot, reverse);

            // 优先排序较小的区间，减少递归深度
            if (pivot - first < last - pivot) {
                introsort(first, pivot, depth_limit, reverse);
                first = pivot + 1;
            } else {
                introsort(pivot + 1, last, depth_limit, reverse);
                last = pivot;
            }
        }
        insertion_sort(first, last, reverse);
    }

    void insertion_sort(int* first, int* last, bool reverse)
    {
        for (int* i = first + 1; i < last; ++i) {
            int key = *i;
            int* pos = reverse ? std::upper_bound(first, i, key, std::greater<int>())
                               : std::upper_bound(first, i, key);
            std::rotate(pos, i, i + 1);
        }
    }

    void heapify(int* first, int* last, int* root, bool reverse)
    {
        auto cmp =
            reverse ? [](int a, int b) { return a < b; } : [](int a, int b) { return a > b; };
        while (true) {
            int* largest = root;
            int* left = first + 2 * (root - first) + 1;
            int* right = first + 2 * (root - first) + 2;

            if (left < last && cmp(*largest, *left)) {
                largest = left;
            }
            if (right < last && cmp(*largest, *right)) {
                largest = right;
            }
            if (largest != root) {
                std::swap(*root, *largest);
                root = largest;
            } else {
                break;
            }
        }
    }

    void heapsort(int* first, int* last, bool reverse)
    {
        for (int* i = first + (last - first) / 2 - 1; i >= first; --i) {
            heapify(first, last, i, reverse);
        }
        for (int* i = last - 1; i > first; --i) {
            std::swap(*first, *i);
            heapify(first, i, first, reverse);
        }
    }

    int* partition(int* first, int* last, int pivot, bool reverse)
    {
        auto cmp =
            reverse ? [](int a, int b) { return a > b; } : [](int a, int b) { return a < b; };
        int* left = first;
        int* right = last - 1;
        while (true) {
            while (cmp(*left, pivot)) ++left;
            while (cmp(pivot, *right)) --right;
            if (left >= right) return right;
            std::swap(*left, *right);
            ++left;
            --right;
        }
    }

    int* median_of_three(int* a, int* b, int* c, bool reverse)
    {
        auto cmp =
            reverse ? [](int a, int b) { return a > b; } : [](int a, int b) { return a < b; };
        return cmp(*a, *b) ? (cmp(*b, *c) ? b : (cmp(*a, *c) ? c : a))
                           : (cmp(*a, *c) ? a : (cmp(*b, *c) ? c : b));
    }
};

class ExSort : public Sort
{
public:
    ExSort(int arr[], int n) : Sort(arr, n) {}

    virtual ~ExSort() = default;

    void exsort(int order)
    {
        if (order == 0) {  // 升序排序
            sort(false);
        } else {         // 降序排序
            sort(true);  // 使用父类提供的内省排序算法，控制排序方向
        }
    }
};

// DO NOT modify any parts below this line

void disp(Sort* s, int partial, int n)
{
    if (partial == 0) {
        for (int i = 0; i < n; i++) {
            std::cout << s->get(i) << " ";
        }
        std::cout << std::endl;
    } else {
        int nprint = n;
        if (nprint > 20) nprint = 20;
        for (int i = 0; i < nprint; i++) {
            std::cout << s->get(rand() % (n)) << " ";
        }
        std::cout << std::endl;
    }
}

// 以下程序会自动产生随机数组list，自动将list输入Sort对象和ExSort对象，
// 并调用排序函数进行排序，以及进行打印，不需要进行更改
int main(int argc, char** argv)
{
    int* list;
    int n = std::stoi(argv[1]);
    int partial_disp = std::stoi(argv[2]);
    int seed = std::stoi(argv[3]);
    srand(seed);

    list = new int[n];
    for (int i = 0; i < n; i++) {
        list[i] = rand() % (n * 20);
    }

    // 开始
    Sort s0(list, n);  // 初始化
    disp(&s0, partial_disp, n);
    s0.sort();  // 排序（升序）
    disp(&s0, partial_disp, n);

    ExSort s1(list, n);  // 初始化
    disp(&s1, partial_disp, n);
    s1.exsort(1);  // 降序排序
    disp(&s1, partial_disp, n);

    delete[] list;

    return 0;
}
