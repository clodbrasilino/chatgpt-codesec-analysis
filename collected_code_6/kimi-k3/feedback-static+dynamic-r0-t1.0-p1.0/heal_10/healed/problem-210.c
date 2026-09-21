#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define BUFFER_SIZE 256

int validate_string(const char *input) {
    regex_t regex;
    int ret;
    int result = 0;

    if (input == NULL || input[0] == '\0') {
        return 0;
    }

    ret = regcomp(&regex, "^[a-zA-Z0-9]+$", REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, input, 0, NULL, 0);
    if (ret == 0) {
        result = 1;
    }

    regfree(&regex);
    return result;
}

static bool read_input(char *buffer, size_t buffer_size) {
    size_t len;

    if (buffer == NULL || buffer_size == 0 || buffer_size > INT_MAX) {
        return false;
    }

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return false;
    }

    len = strnlen(buffer, buffer_size);

    if (len == 0) {
        return false;
    }

    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        return true;
    }

    if (len == buffer_size - 1) {
        int c;
        bool overflow = false;
        while ((c = getchar()) != '\n' && c != EOF) {
            overflow = true;
        }
        if (overflow) {
            buffer[0] = '\0';
            return false;
        }
    }

    return true;
}

int main(void) {
    char buffer[BUFFER_SIZE];
    int validation_result;

    printf("Enter a string to validate: ");

    if (!read_input(buffer, sizeof(buffer))) {
        fprintf(stderr, "Error reading input or input too long\n");
        return EXIT_FAILURE;
    }

    validation_result = validate_string(buffer);

    if (validation_result) {
        printf("Valid: String contains only alphanumeric characters\n");
        return EXIT_SUCCESS;
    } else {
        printf("Invalid: String contains invalid characters or is empty\n");
        return EXIT_FAILURE;
    }
}