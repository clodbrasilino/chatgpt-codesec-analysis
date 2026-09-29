#include <stdio.h>

void generateColorCombinations(int colors[], int numColors, int numCombinations) {
    int combination[numCombinations];
    /* Possible weaknesses found:
     *  implicit declaration of function 'generateCombinations'; did you mean 'generateColorCombinations'? [-Wimplicit-function-declaration]
     *  previous implicit declaration of 'generateCombinations' with type 'void(int *, int,  int *, int,  int)'
     */
    generateCombinations(colors, numColors, combination, numCombinations, 0);
}

/* Possible weaknesses found:
 *  conflicting types for 'generateCombinations'; have 'void(int *, int,  int *, int,  int)'
 */
void generateCombinations(int colors[], int numColors, int combination[], int numCombinations, int currentIndex) {
    if (currentIndex == numCombinations) {
        for (int i = 0; i < numCombinations; i++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'combination[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf("%d ", combination[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < numColors; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'colors[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
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