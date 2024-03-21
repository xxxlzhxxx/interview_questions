#include <iostream>
#include <list>
#include <vector>

class HashTable {
public:
    HashTable(int size) : table(size) {}

    // 插入键值对
    void insert(int key, int value) {
        int index = hashFunction(key);
        auto& list = table[index];
        for (auto& pair : list) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        list.emplace_back(key, value);
    }

    // 查找键对应的值
    bool find(int key, int& value) {
        int index = hashFunction(key);
        auto& list = table[index];
        for (auto& pair : list) {
            if (pair.first == key) {
                value = pair.second;
                return true;
            }
        }
        return false;
    }

    // 删除键值对
    bool remove(int key) {
        int index = hashFunction(key);
        auto& list = table[index];
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (it->first == key) {
                list.erase(it);
                return true;
            }
        }
        return false;
    }


};








int main() {
    HashTable ht(10);

    // 插入键值对
    ht.insert(1, 10);
    ht.insert(2, 20);
    ht.insert(11, 110);

    // 查找键对应的值
    int value;
    if (ht.find(2, value)) {
        std::cout << "Value for key 2 is " << value << std::endl;
    }
    return 0;
}
