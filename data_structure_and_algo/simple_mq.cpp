#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

template<typename T>
class SimpleMessageQueue {

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable condition_;


public:
    // 向队列中添加消息
    void push(const T& message) {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(message);
        condition_.notify_one(); // 通知一个等待的线程
    }

    // 从队列中取出消息
    T pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        // 等待直到队列不为空
        condition_.wait(lock, [this] { return !queue_.empty(); });
        T message = queue_.front();
        queue_.pop();
        return message;
    }
};










// 示例用法
int main() {
    SimpleMessageQueue<int> queue;

    // 生产者线程
    std::thread producer([&queue]() {
        for (int i = 0; i < 10; ++i) {
            std::cout << "Producing " << i << std::endl;
            queue.push(i);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    // 消费者线程
    std::thread consumer([&queue]() {
        for (int i = 0; i < 10; ++i) {
            int message = queue.pop();
            std::cout << "Consuming " << message << std::endl;
        }
    });

    producer.join();
    consumer.join();

    return 0;
}
