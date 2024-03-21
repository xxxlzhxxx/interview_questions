#include <iostream>
#include <vector>

// 交换两个元素
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// 划分函数
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];    // 选择最后一个元素作为基准
    int i = low - 1;          // 小于基准的元素的索引

    for (int j = low; j <= high - 1; j++) {
        // 如果当前元素小于或等于基准
        if (arr[j] <= pivot) {
            i++;    // 移动小于基准的元素的索引
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// 快速排序函数
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        // 找到划分点
        int pi = partition(arr, low, high);

        // 对左右子数组进行递归排序
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();

    quickSort(arr, 0, n - 1);

    std::cout << "Sorted array: \n";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
