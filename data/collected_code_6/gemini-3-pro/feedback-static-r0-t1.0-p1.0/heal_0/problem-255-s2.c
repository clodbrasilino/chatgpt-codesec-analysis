#include <stdio.h>
#include <stdlib.h>

void generateCombinations(char *colors, int n, int k, char *currentCombination, int index, int start) {
    if (index == k) {
        for (int i = 0; i < k; i++) {
            printf("%c ", currentCombination[i]);
        }
        printf("\n");
        return;
    }

    for (int i = start; i < n; i++) {
        currentCombination[index] = colors[i];
        generateCombinations(colors, n, k, currentCombination, index, i);
    }
}

void printCombinations(int k) {
    if (k <= 0) {
        return;
    }

    char colors[] = {'R', 'G', 'B'};
    int n = sizeof(colors) / sizeof(colors[0]);

    char *currentCombination = (char *)malloc(k * sizeof(char));
    if (currentCombination == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    generateCombinations(colors, n, k, currentCombination, 0, 0);

    free(currentCombination);
}

int main(void) {
    int k = 2;
    printCombinations(k);
    return 0;
}