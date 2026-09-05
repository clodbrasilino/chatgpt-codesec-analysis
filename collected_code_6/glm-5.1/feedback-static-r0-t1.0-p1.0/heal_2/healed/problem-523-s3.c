#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int validate_string(const char *str, size_t req_len) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strlen(str);

    if (len != req_len) {
        return 0;
    }

    int has_upper = 0;
    int has_lower = 0;
    int has_digit = 0;

    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)str[i])) {
            has_upper = 1;
        } else if (islower((unsigned char)str[i])) {
            has_lower = 1;
        } else if (isdigit((unsigned char)str[i])) {
            has_digit = 1;
        }
    }

    return has_upper && has_lower && has_digit;
}

int main(int argc, char * const * const argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long req_len = strtol(argv[2], &endptr, 10);

    if (*endptr != '\0' || req_len < 0) {
        fprintf(stderr, "Invalid length provided.\n");
        return EXIT_FAILURE;
    }

    int result = validate_string(argv[1], (size_t)req_len);

    if (result) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }

    return EXIT_SUCCESS;
}