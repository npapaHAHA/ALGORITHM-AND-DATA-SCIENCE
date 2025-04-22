#include <iostream>

int main() {
    int numberHorses;
    std::cin >> numberHorses;

    int horseHeights[numberHorses];
    for (int i = 0; i < numberHorses; i++) {
        std::cin >> horseHeights[i];
    }

    int currentHeight;
    for (int i = numberHorses - 1; i >= 0; i--) {
        int j;
        currentHeight = horseHeights[i];
        for (j = i + 1; j < numberHorses && horseHeights[j] < currentHeight; j++) {
            int tugriksAfterReplacement = currentHeight - horseHeights[j];
            int distanceBetweenHorses = j - i;

            if (tugriksAfterReplacement == 1) {
                std::cout << ":(";
                return 0;
            }

            horseHeights[j - 1] = horseHeights[j] + 1;
            currentHeight--;
        }
        horseHeights[j - 1] = currentHeight;
    }

    for (int i = 0; i < numberHorses; i++) {
        std::cout << horseHeights[i] << " ";
    }
}