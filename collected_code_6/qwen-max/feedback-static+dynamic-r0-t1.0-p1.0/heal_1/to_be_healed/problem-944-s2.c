#include <stdio.h>
#include <ctype.h>
#include <string.h>

void print_numbers_and_positions(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    for (size_t i = 0, len = strlen(str); i < len; ++i) {
        if (isdigit(str[i])) {
            printf("Number: %c, Position: %zu\n", str[i], i);
        }
    }
}

int main() {
    const char *input = "a1b2c3d4";
    print_numbers_and_positions(input);
    return 0;
}