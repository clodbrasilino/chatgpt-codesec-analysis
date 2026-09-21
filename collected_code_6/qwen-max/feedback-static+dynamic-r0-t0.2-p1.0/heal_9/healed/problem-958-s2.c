#include <stdio.h>
#include <stdlib.h>

char* intToRoman(int num) {
    char *roman = (char *)malloc(20 * sizeof(char));
    if (!roman) return NULL;
    roman[0] = '\0';
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int len = 0;
    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            len += snprintf(roman + len, 20 - len, "%s", symbols[i]);
            num -= values[i];
        }
    }
    return roman;
}

int main() {
    int test_cases[] = {1, 4, 50};
    int n_tests = 3;

    for (int i = 0; i < n_tests; i++) {
        int number = test_cases[i];
        char *roman = intToRoman(number);
        if (roman) {
            printf("%d in Roman numerals is: %s\n", number, roman);
            free(roman);
        } else {
            printf("Memory allocation failed.\n");
        }
    }

    return 0;
}