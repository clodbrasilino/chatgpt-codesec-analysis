#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int starts_with_number(const char *str, int number) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char num_str[12];
    snprintf(num_str, sizeof(num_str), "%d", number);
    size_t len = strnlen(num_str, sizeof(num_str));
    return strncmp(str, num_str, len) == 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <string> <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_string = argv[1];
    char *end;
    long input_number = strtol(argv[2], &end, 10);

    if (end == argv[2] || *end != '\0' || input_number > INT_MAX || input_number < INT_MIN) {
        printf("Invalid number format.\n");
        return EXIT_FAILURE;
    }

    if (starts_with_number(input_string, (int)input_number)) {
        printf("The string '%s' starts with the number %ld.\n", input_string, input_number);
    } else {
        printf("The string '%s' does not start with the number %ld.\n", input_string, input_number);
    }

    return EXIT_SUCCESS;
}