#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int romanToInt(const char *s) {
    static const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    static const char *roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const char *p = s;
    int i, result = 0;

    while (*p) {
        for (i = 0; i < 13; ++i) {
            size_t len = strlen(roman[i]);
            if (strncmp(p, roman[i], len) == 0 && (p[len] == '\0' || strchr("MDCLXVI", p[len]) != NULL)) {
                result += values[i];
                p += len;
                break;
            }
        }
        if (i == 13) {
            return -1;
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

    if (strlen(input) > 15 || !strspn(input, "MDCLXVI")) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int output = romanToInt(input);
    if (output == -1) {
        fprintf(stderr, "Invalid Roman numeral\n");
        return EXIT_FAILURE;
    }

    printf("The integer value is: %d\n", output);
    return 0;
}