#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int is_integer(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }

    if (*str == '+' || *str == '-') {
        str++;
    }

    if (*str == '\0') {
        return 0;
    }

    while (*str) {
        if (!isdigit((unsigned char)*str)) {
            return 0;
        }
        str++;
    }

    return 1;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    if (is_integer(input)) {
        printf("The string represents an integer.\n");
    } else {
        printf("The string does not represent an integer.\n");
    }

    return 0;
}