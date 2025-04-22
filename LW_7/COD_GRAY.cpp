#include <iostream>
#include <vector>
#include <string>

void generateGrayCode(int numBits, std::vector<int>& graySequence) {
    int totalNumbers = 1 << numBits;
    for (int i = 0; i < totalNumbers; ++i) {
        int gray = i ^ (i >> 1);
        graySequence.push_back(gray);
    }
}

std::string convertToBinary(int number, int bitLength) {
    std::string binaryStr;
    for (int i = bitLength - 1; i >= 0; --i) {
        binaryStr += (number & (1 << i)) ? '1' : '0';
    }
    return binaryStr;
}

int main() {
    int numBits;
    std::cin >> numBits;

    std::vector<int> grayCodeSequence;
    generateGrayCode(numBits, grayCodeSequence);

    for (const auto& num : grayCodeSequence) {
        std::string binaryString = convertToBinary(num, numBits);
        std::cout << binaryString << std::endl;
    }

    return 0;
}
