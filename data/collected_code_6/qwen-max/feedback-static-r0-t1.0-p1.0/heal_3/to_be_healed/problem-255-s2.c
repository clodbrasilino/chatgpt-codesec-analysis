#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateCombinations(const char *colors, int numColors, int toChoose, char *combination, int at, int index) {
    if (index == toChoose) {
        combination[index] = '\0';
        printf("%s\n", combination);
        return;
    }
    for (int i = 0; i < numColors; ++i) {
        combination[index] = colors[i];
        generateCombinations(colors, numColors, toChoose, combination, i, index + 1);
    }
}

int main() {
    const char colors[] = "RGB";
    int numColors = 3;
    int toChoose = 2;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char combination[toChoose + 1];
    memset(combination, 0, sizeof(combination));
    generateCombinations(colors, numColors, toChoose, combination, 0, 0);
    return 0;
}