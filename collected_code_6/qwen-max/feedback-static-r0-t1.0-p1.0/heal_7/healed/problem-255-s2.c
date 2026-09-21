#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateCombinations(const char *colors, int numColors, int toChoose, char *combination, int index) {
    if (index == toChoose) {
        printf("%s\n", combination);
        return;
    }
    for (int i = 0; i < numColors; ++i) {
        combination[index] = colors[i];
        generateCombinations(colors, numColors, toChoose, combination, index + 1);
    }
}

int main() {
    const char colors[] = "RGB";
    int numColors = sizeof(colors) - 1;
    int toChoose = 2;
    char combination[toChoose + 1];
    memset(combination, 0, toChoose + 1);
    generateCombinations(colors, numColors, toChoose, combination, 0);
    return 0;
}