#include <iostream>
#include <mutex>
#include <vector>
#include <optional>
#include <condition_variable>

template <typename T>
class ThreadSafeCircularQueue {
private:
    size_t capacity_;
    size_t head_;
    size_t tail_;
    size_t size_;
    std::vector<T> data_;
    mutable std::mutex mutex_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
public:
    ThreadSafeCircularQueue(size_t capacity) : capacity_(capacity), head_(0), tail_(0), size_(0), data_(capacity) {}

    void enqueue(const T& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        not_full_.wait(lock, [this] { return size_ < capacity_; });
        data_[tail_] = item;
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
        not_empty_.notify_one();
    }

    bool dequeue(T& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        not_empty_.wait(lock, [this] { return size_ > 0; });
        item = data_[head_];
        head_ = (head_ + 1) % capacity_;
        --size_;
        not_full_.notify_one();
        return true;
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

    int item;
    while (queue.dequeue(item)) {
        std::cout << "Dequeued: " << item << std::endl;
    }

    return 0;
}
