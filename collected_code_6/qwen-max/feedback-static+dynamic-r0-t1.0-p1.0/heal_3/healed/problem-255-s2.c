#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateCombinations(char *colors, int numColors, int toChoose, char *combination, int at, int index, int *comboLength) {
    if (index == toChoose) {
        combination[index] = '\0';
        printf("%s\n", combination);
        return;
    }
    for (int i = 0; i < numColors; ++i) {
        if (index + 1 <= toChoose) {
            combination[index] = colors[i];
            generateCombinations(colors, numColors, toChoose, combination, i, index + 1, comboLength);
        }
    }
}

int main() {
    char colors[] = "RGB";
    int numColors = 3;
    int toChoose = 2;
    char *combination = (char *)malloc((toChoose + 1) * sizeof(char));
    if (combination == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    combination[toChoose] = '\0';
    int comboLength = toChoose;
    generateCombinations(colors, numColors, toChoose, combination, 0, 0, &comboLength);
    free(combination);
    return 0;
}