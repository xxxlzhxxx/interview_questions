#include <iostream>
#include <list>
#include <vector>

class MyUnorderedMap {
public:
    MyUnorderedMap() : buckets_(initial_buckets_size), size_(0) {}

    void insert(int key, int value) {
        size_t index = hash(key) % buckets_.size();
        for (auto& pair : buckets_[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        buckets_[index].emplace_back(key, value);
        ++size_;
        if (buckets_[index].size() > max_chain_length) {
            rehash();
        }
    }

    int get(int key) {
        size_t index = hash(key) % buckets_.size();
        for (auto& pair : buckets_[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return -1; // Key not found
    }

    void remove(int key) {
        size_t index = hash(key) % buckets_.size();
        auto& chain = buckets_[index];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->first == key) {
                chain.erase(it);
                --size_;
                return;
            }
        }
    }

private:
    std::vector<std::list<std::pair<int, int>>> buckets_;
    size_t size_;
    static const size_t initial_buckets_size = 4;
    static const size_t max_chain_length = 4;

    size_t hash(int key) {
        return std::hash<int>{}(key);
    }

    void rehash() {
        std::vector<std::list<std::pair<int, int>>> new_buckets(buckets_.size() * 2);
        for (auto& chain : buckets_) {
            for (auto& pair : chain) {
                size_t index = hash(pair.first) % new_buckets.size();
                new_buckets[index].emplace_back(pair);
            }
        }
        buckets_ = std::move(new_buckets);
    }
};

int main() {
    MyUnorderedMap map;
    map.insert(1, 100);
    map.insert(2, 200);
    map.insert(3, 300);
    map.insert(4, 400);
    map.insert(5, 500); // This should trigger a rehash

    std::cout << "Value for key 3: " << map.get(3) << std::endl;
    map.remove(3);
    std::cout << "Value for key 3 after removal: " << map.get(3) << std::endl;

    return 0;
}
