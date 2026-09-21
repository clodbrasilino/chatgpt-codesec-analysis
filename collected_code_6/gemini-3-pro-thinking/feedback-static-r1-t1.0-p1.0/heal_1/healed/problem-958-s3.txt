#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    const char *symbol;
} RomanNumeral;

int int_to_roman(int num, char *buffer, size_t buffer_size);

int int_to_roman(int num, char *buffer, size_t buffer_size) {
    if (num < 1 || num > 3999 || buffer == NULL || buffer_size == 0) {
        return -1;
    }

    const RomanNumeral numerals[] = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };

    size_t current_len = 0;
    size_t num_numerals = sizeof(numerals) / sizeof(numerals[0]);

    for (size_t i = 0; i < num_numerals; ++i) {
        while (num >= numerals[i].value) {
            const char *sym = numerals[i].symbol;
            while (*sym != '\0') {
                if (current_len + 1 >= buffer_size) {
                    return -1;
                }
                buffer[current_len++] = *sym++;
            }
            num -= numerals[i].value;
        }
    }
    
    buffer[current_len] = '\0';
    return 0;
}

int main(void) {
    size_t buffer_size = 32;
    char *buffer = (char *)malloc(buffer_size * sizeof(char));
    
    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    int test_numbers[] = {3999, 1994, 58, 9, 4, 1, 0, 4000};
    size_t num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);

    for (size_t i = 0; i < num_tests; ++i) {
        if (int_to_roman(test_numbers[i], buffer, buffer_size) == 0) {
            printf("%d -> %s\n", test_numbers[i], buffer);
        } else {
            printf("%d -> Invalid input or insufficient buffer\n", test_numbers[i]);
        }
    }

    free(buffer);
    return EXIT_SUCCESS;
}