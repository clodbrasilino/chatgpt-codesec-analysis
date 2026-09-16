#include <stdio.h>
#include <stdlib.h>

char *int_to_roman(int num) {
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int count = (int)(sizeof(values) / sizeof(values[0]));
    int i;
    char *roman;
    char *dst;

    if (num <= 0 || num > 3999) {
        return NULL;
    }

    roman = malloc(16 * sizeof(*roman));
    if (roman == NULL) {
        return NULL;
    }

    dst = roman;

    for (i = 0; i < count; i++) {
        while (num >= values[i]) {
            const char *sym = symbols[i];
            while (*sym) {
                *dst++ = *sym++;
            }
            num -= values[i];
        }
    }

    *dst = '\0';
    return roman;
}

int main(void) {
    int test_values[] = {0, 1, 4, 9, 58, 1994, 3888, 3999, 4000, -5};
    int count = (int)(sizeof(test_values) / sizeof(test_values[0]));
    int i;

    for (i = 0; i < count; i++) {
        char *roman = int_to_roman(test_values[i]);
        if (roman != NULL) {
            printf("%d = %s\n", test_values[i], roman);
            free(roman);
        } else {
            printf("%d = Invalid input\n", test_values[i]);
        }
    }

    return 0;
}