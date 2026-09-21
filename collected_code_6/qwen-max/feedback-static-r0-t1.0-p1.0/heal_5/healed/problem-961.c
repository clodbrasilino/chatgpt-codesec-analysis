#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int romanToInt(const char *s) {
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const size_t len_values = sizeof(values) / sizeof(values[0]);
    const char *p = s;
    int result = 0;

    while (*p) {
        for (size_t i = 0; i < len_values; ++i) {
            size_t len = strlen(roman[i]);
            if (strncmp(p, roman[i], len) == 0) {
                result += values[i];
                p += len;
                break;
            }
        }
    }

    return result;
}

int main() {
    char input[16];
    printf("Enter a Roman numeral: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) > 15 || strlen(input) == 0) {
            fprintf(stderr, "Input too long or empty\n");
            return EXIT_FAILURE;
        }
        int output = romanToInt(input);
        printf("The integer value is: %d\n", output);
    } else {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    return 0;
}