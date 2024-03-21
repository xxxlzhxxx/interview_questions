#include <iostream>
#include <vector>
#include <stdexcept>

class Bitmap {

private:
    std::vector<char> bits;
    
public:
    Bitmap(size_t size) : bits((size + 7) / 8, 0) {}

    void setBit(size_t pos) {
        if (pos >= bits.size() * 8) {
            throw std::out_of_range("Bit position out of range");
        }
        bits[pos / 8] |= (1 << (pos % 8));
    }

    void clearBit(size_t pos) {
        if (pos >= bits.size() * 8) {
            throw std::out_of_range("Bit position out of range");
        }
        bits[pos / 8] &= ~(1 << (pos % 8));
    }

    bool getBit(size_t pos) const {
        if (pos >= bits.size() * 8) {
            throw std::out_of_range("Bit position out of range");
        }
        return (bits[pos / 8] & (1 << (pos % 8))) != 0;
    }
};







int main() {
    Bitmap bitmap(32);

    // 设置和清除位
    bitmap.setBit(3);
    bitmap.setBit(10);
    bitmap.clearBit(3);

    // 检查位的状态
    std::cout << "Bit 3: " << bitmap.getBit(3) << std::endl;
    std::cout << "Bit 10: " << bitmap.getBit(10) << std::endl;

    return 0;
}
