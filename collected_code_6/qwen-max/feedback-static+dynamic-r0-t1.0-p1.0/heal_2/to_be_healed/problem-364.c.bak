#include <stdio.h>
#include <string.h>

int countFlipsToAlternate(const char *str) {
    int flipsFor01 = 0, flipsFor10 = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if ((i % 2 == 0 && str[i] != '0') || (i % 2 != 0 && str[i] != '1')) {
            flipsFor01++;
        } else if ((i % 2 == 0 && str[i] != '1') || (i % 2 != 0 && str[i] != '0')) {
            flipsFor10++;
        }
    }
    return flipsFor01 < flipsFor10 ? flipsFor01 : flipsFor10;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'binaryStr' can be declared as const array [constVariable]
     */
    char binaryStr[] = "00101010";
    int minFlips = countFlipsToAlternate(binaryStr);
    printf("Minimum number of flips: %d\n", minFlips);
    return 0;
}