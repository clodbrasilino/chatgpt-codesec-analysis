#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

int starts_with_number(const char *str, int number) {
    char num_str[21];
    snprintf(num_str, sizeof(num_str), "%d", number);
    size_t num_len = strnlen(num_str, sizeof(num_str));
    if (num_len > 0 && strncasecmp(str, num_str, num_len) == 0 && (str[num_len] == '\0' || !isdigit((unsigned char)str[num_len]))) {
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