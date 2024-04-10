#include <iostream>
#include <mutex>
#include <vector>
#include <optional>

template <typename T>
class ThreadSafeCircularQueue {
private:
    size_t capacity_;
    size_t head_;
    size_t tail_;
    size_t size_;
    std::vector<T> data_;
    mutable std::mutex mutex_;

    
public:
    ThreadSafeCircularQueue(size_t capacity) : capacity_(capacity), head_(0), tail_(0), size_(0), data_(capacity) {}

    void enqueue(const T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (size_ == capacity_) {
            // 队列已满，覆盖最早的元素
            head_ = (head_ + 1) % capacity_;
            --size_;
        }
        data_[tail_] = item;
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    bool dequeue(T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (size_ == 0) {
            return false; // 队列为空
        }
        item = data_[head_];
        head_ = (head_ + 1) % capacity_;
        --size_;
        return true;
    }

    std::optional<T> peekFront() const {
        std::lock_guard<std::mutex> lock(mutex_);
        if (size_ == 0) {
            return {}; // 队列为空
        }
        return data_[head_];
    }

    std::optional<T> peekBack() const {
        std::lock_guard<std::mutex> lock(mutex_);
        if (size_ == 0) {
            return {}; // 队列为空
        }
        return data_[(tail_ + capacity_ - 1) % capacity_];
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return size_;
    }

    bool isEmpty() const {
        return size() == 0;
    }

    bool isFull() const {
        return size() == capacity_;
    }


};

int main() {
    ThreadSafeCircularQueue<int> queue(3);

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4); // This will overwrite 1

    int item;
    while (queue.dequeue(item)) {
        std::cout << "Dequeued: " << item << std::endl;
    }

    return 0;
}
