#include <iostream>
#include <string>
int preprocess(char x) {
    int position_in_alph = (int) x;
    return position_in_alph -97;
}

void radixSort(std::string A[], int n, int k, int t) {
    std::string* B = new std::string[n];
    int eng_alphabet = 26;
    int* C = new int[eng_alphabet];

    for (int i = 1; i <= t; i++) {
        for (int j =0; j < eng_alphabet; j++) {
            C[j] = 0;

        }
        for (int j = 0; j < n; j++) {
            int d = preprocess(A[j][k - i]);
            C[d]++;
        }

        int count = 0;

        for (int j = 0; j < eng_alphabet; j++) {

            int tmp = C[j];
            C[j] = count;
            count += tmp;


        }

        for (int j = 0; j < n; j++) {
            int d = preprocess(A[j][k - i]);
            B[C[d]] = A[j];
            C[d]++;
        }

        for (int j = 0; j < n; j++) {
            A[j] = B[j];
        }
    }

    delete[] B;
    delete[] C;
}

int main() {
   int n, k, t;
    std::cin >> n >> k >> t;

    std::string* messages = new std::string[n];

    for (int i = 0; i < n; i++) {
        std::cin >> messages[i];
    }
    radixSort(messages, n, k, t);

    for (int i = 0; i < n; i++) {
        std::cout << messages[i] << "\n";
    }

    delete[] messages;
}