#include <iostream>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;  // Читаем значения N и K

    int numbers[N]; 
    for (int i = 0; i < N; i++) {
        cin >> numbers[i];  
    }

    
    K = K % N;

    if (K > 0) {  
        for (int i = 0; i < K; i++) {
            int temp_num = numbers[N-1];  
            for (int j = N - 2; j >= 0; j--) {
                numbers[j + 1] = numbers[j];  
            }
            numbers[0] = temp_num; 
        }
    } else if (K < 0) {  
        K = -K;
        for (int i = 0; i < K; i++) {
            int temp_num = numbers[0]; 
            for (int j = 0; j < N - 1; j++) {
                numbers[j] = numbers[j + 1];  
            }
            numbers[N - 1] = temp_num; 
        }
    }

   
    for (int i = 0; i < N; i++) {
        cout << numbers[i] << " ";
    }

    return 0;
}
