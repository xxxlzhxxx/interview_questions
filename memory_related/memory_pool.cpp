#include <iostream>
#include <list>
#include <cassert>

class MemoryPool {

    size_t blockSize;                         // 内存块大小
    size_t blockCount;                        // 内存块数量
    std::list<char*> freeBlocks;              // 空闲内存块列表

public:
    MemoryPool(size_t blockSize, size_t blockCount) 
        : blockSize(blockSize), blockCount(blockCount) {
        // 初始化内存池
        for (size_t i = 0; i < blockCount; ++i) {
            freeBlocks.push_back(new char[blockSize]);
        }
    }

    ~MemoryPool() {
        // 释放内存池
        for (char* block : freeBlocks) {
            delete[] block;
        }
    }

    void* allocate() {
        // 分配内存块
        assert(!freeBlocks.empty()); // 确保还有空闲块
        char* block = freeBlocks.front();
        freeBlocks.pop_front();
        return block;
    }

    void deallocate(void* block) {
        // 回收内存块
        freeBlocks.push_back(static_cast<char*>(block));
    }
};

int main() {
    const size_t blockSize = 128; // 每个内存块大小
    const size_t blockCount = 10; // 内存块数量

    MemoryPool pool(blockSize, blockCount);

    // 分配和回收内存
    void* ptr1 = pool.allocate();
    void* ptr2 = pool.allocate();
    pool.deallocate(ptr1);
    void* ptr3 = pool.allocate();

    // 检查内存块是否重复使用
    assert(ptr1 == ptr3);

    return 0;
}
