#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int starts_with_number(const char *str, int number) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char num_str[20]; // Use a fixed size buffer that can hold any integer value in decimal format
    snprintf(num_str, sizeof(num_str), "%d", number);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strncasecmp(str, num_str, strlen(num_str)) == 0) {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <string> <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_string = argv[1];
    char *endptr;
    errno = 0;
    long input_number = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || (errno == ERANGE && (input_number == LONG_MIN || input_number == LONG_MAX)) || input_number < INT_MIN || input_number > INT_MAX) {
        printf("Invalid number: %s\n", argv[2]);
        return EXIT_FAILURE;
    }

    if (starts_with_number(input_string, (int)input_number)) {
        printf("The string '%s' starts with the number %ld.\n", input_string, input_number);
    } else {
        printf("The string '%s' does not start with the number %ld.\n", input_string, input_number);
    }

    return EXIT_SUCCESS;
}