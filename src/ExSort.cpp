#include "../include/ExSort.h"

ExSort::ExSort(const int arr[], int n) : Sort(arr, n) {}

void ExSort::exsort(int order)
{
    // order为0时升序排序，否则降序排序
    sort(order != 0);
}