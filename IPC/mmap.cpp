#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

int main() {
    // 打开一个文件
    int fd = open("example.txt", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // 调整文件大小
    if (ftruncate(fd, 1024) == -1) {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    // 将文件映射到内存
    char *mapped = (char *)mmap(nullptr, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    // 使用内存映射区域
    strcpy(mapped, "Hello, Memory-mapped File!");
    std::cout << "Read from memory-mapped file: " << mapped << std::endl;

    // 清理资源
    if (munmap(mapped, 1024) == -1) {
        perror("munmap");
    }

    close(fd);
    return 0;
}
