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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char combination[toChoose + 1];
    combination[toChoose] = '\0';
    int comboLength = toChoose;
    generateCombinations(colors, numColors, toChoose, combination, 0, 0, &comboLength);
    return 0;
}