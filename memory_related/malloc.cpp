#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr;
    int n = 5; // 数组大小

    // 分配内存
    arr = (int *)malloc(n * sizeof(int));

    // 检查内存分配是否成功
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // 初始化数组
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // 打印数组
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 释放内存
    free(arr);

    int rows = 3;
    int cols = 4;
    int **matrix;

    // 分配行指针
    matrix = (int **)malloc(rows * sizeof(int *));

    // 分配每一行
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }

    // 初始化矩阵
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j;
        }
    }

    // 打印矩阵
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // 释放内存
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);


    return 0;
}
