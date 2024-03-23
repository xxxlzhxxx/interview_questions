#include <iostream>
#include <vector>

void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;       // 初始化最大元素为根
    int left = 2 * i + 1;  // 左子节点
    int right = 2 * i + 2; // 右子节点

    // 如果左子节点大于根
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // 如果右子节点大于目前最大的元素
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // 如果最大元素不是根
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        // 递归地构建子树
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();

    // 构建最大堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // 一个个从堆顶取出元素
    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);
        // 对剩余的堆进行调整
        heapify(arr, i, 0);
    }
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    heapSort(arr);

    std::cout << "Sorted array is \n";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
