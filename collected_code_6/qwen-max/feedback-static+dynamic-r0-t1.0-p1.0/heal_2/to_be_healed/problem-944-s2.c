#include <stdio.h>
#include <ctype.h>
#include <string.h>

void print_numbers_and_positions(const char *str, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        if (isdigit(str[i])) {
            printf("Number: %c, Position: %zu\n", str[i], i);
        }
    }
}

int main() {
    const char *input = "a1b2c3d4";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    print_numbers_and_positions(input, input_len);
    return 0;
}