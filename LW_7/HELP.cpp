#include <iostream>
#include <vector>
#include <string>

using namespace std;

string correctHamming(const string& inputCode) {
    int length = inputCode.length();
    int errorIdx = 0;

    for (int power = 0; (1 << power) <= length; ++power) {
        int checkBit = (1 << power);
        int parity = 0;

        for (int pos = 1; pos <= length; ++pos) {
            if (pos & checkBit) {
                parity ^= (inputCode[pos - 1] - '0');
            }
        }

        if (parity != 0) {
            errorIdx += checkBit;
        }
    }

    string correctedCode = inputCode;
    if (errorIdx > 0 && errorIdx <= length) {
        correctedCode[errorIdx - 1] = (correctedCode[errorIdx - 1] == '0') ? '1' : '0';
    }

    string dataBits;
    for (int pos = 1; pos <= length; ++pos) {
        if ((pos & (pos - 1)) != 0) {
            dataBits += correctedCode[pos - 1];
        }
    }

    return dataBits;
}

int main() {
    int testCases;
    cin >> testCases;
    cin.ignore();

    vector<string> decodedResults;

    for (int i = 0; i < testCases; ++i) {
        string encodedInput;
        getline(cin, encodedInput);

        string decodedOutput = correctHamming(encodedInput);
        decodedResults.push_back(decodedOutput);
    }

    for (const auto& result : decodedResults) {
        cout << result << '\n';
    }

    return 0;
}
