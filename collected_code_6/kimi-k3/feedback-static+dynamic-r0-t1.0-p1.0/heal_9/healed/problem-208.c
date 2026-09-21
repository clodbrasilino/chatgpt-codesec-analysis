#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>

int validate_decimal_precision(const char *input_str, size_t max_len) {
    if (input_str == NULL || max_len == 0) {
        return 0;
    }

    size_t len = strnlen(input_str, max_len);
    if (len == 0 || len == max_len || len > 255) {
        return 0;
    }

    const char *pattern = "^[+-]?[0-9]+\\.[0-9]{2}$";
    regex_t regex;
    int regex_result;

    regex_result = regcomp(&regex, pattern, REG_EXTENDED);
    if (regex_result != 0) {
        return 0;
    }

    regex_result = regexec(&regex, input_str, 0, NULL, 0);
    regfree(&regex);

    return (regex_result == 0) ? 1 : 0;
}

int main(void) {
    char input_buffer[256];

    printf("Enter a decimal number: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    size_t input_len = strnlen(input_buffer, sizeof(input_buffer));
    if (input_len == 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (input_buffer[input_len - 1] == '\n') {
        input_buffer[input_len - 1] = '\0';
    } else if (input_len == sizeof(input_buffer) - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    if (validate_decimal_precision(input_buffer, sizeof(input_buffer))) {
        printf("Valid decimal with precision 2\n");
    } else {
        printf("Invalid decimal\n");
    }

    return EXIT_SUCCESS;
}