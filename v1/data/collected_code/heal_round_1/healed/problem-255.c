#include <stdio.h>

void generateCombinations(int colors[], int numColors, int combination[], int numCombinations, int currentIndex);

void generateColorCombinations(int colors[], int numColors, int numCombinations) {
    int combination[numCombinations];
    for(int i = 0; i < numCombinations; i++) {
        combination[i] = 0;
    }
    generateCombinations(colors, numColors, combination, numCombinations, 0);
}

void generateCombinations(int colors[], int numColors, int combination[], int numCombinations, int currentIndex) {
    if (currentIndex == numCombinations) {
        for (int i = 0; i < numCombinations; i++) {
            printf("%d ", combination[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < numColors; i++) {
        combination[currentIndex] = colors[i];
        generateCombinations(colors, numColors, combination, numCombinations, currentIndex+1);
    }
}

int main() {
    int colors[] = {1, 2, 3};
    int numColors = sizeof(colors) / sizeof(colors[0]);
    int numCombinations = 3;

    generateColorCombinations(colors, numColors, numCombinations);

    return 0;
}