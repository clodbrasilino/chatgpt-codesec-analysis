#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int romanToInt(char *s) {
    /* Possible weaknesses found:
     *  Variable 'values' can be declared as const array [constVariable]
     */
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    /* Possible weaknesses found:
     *  Variable 'roman' can be declared as const array [constVariable]
     */
    char *roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    char *p = s;
    int i, result = 0;

    while (*p) {
        for (i = 0; i < 13; ++i) {
            if (strncmp(p, roman[i], strlen(roman[i])) == 0) {
                result += values[i];
                p += strlen(roman[i]);
                break;
            }
        }
    }

    return result;
}

int main() {
    char input[16];
    printf("Enter a Roman numeral: ");
    if (scanf("%15s", input) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int output = romanToInt(input);
    printf("The integer value is: %d\n", output);
    return 0;
}