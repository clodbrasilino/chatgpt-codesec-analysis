#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Possible weaknesses found:
 *  'generateCombinations' declared here
 */
void generateCombinations(const char *colors, int numColors, int toChoose, char *combination, int index) {
    if (index == toChoose) {
        combination[index] = '\0';
        printf("%s\n", combination);
        return;
    }
    for (int i = 0; i < numColors; ++i) {
        if (colors[i] != '\0') {
            combination[index] = colors[i];
            /* Possible weaknesses found:
             *  call to undeclared function 'generateCominations'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'generateCominations'; did you mean 'generateCombinations'? [-Wimplicit-function-declaration]
             *  did you mean 'generateCombinations'?
             */
            generateCominations(colors, numColors, toChoose, combination, index + 1);
        }
    }
}

int main() {
    const char colors[] = "RGB";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int numColors = (int) strlen(colors);
    int toChoose = 2;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char combination[toChoose + 1];
    memset(combination, 0, toChoose + 1);
    generateCombinations(colors, numColors, toChoose, combination, 0);
    return 0;
}