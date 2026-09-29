#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int validate_decimal_precision(const char *input_str) {
    if (input_str == NULL) {
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

    size_t len = strlen(input_buffer);
    if (len > 0 && input_buffer[len - 1] == '\n') {
        input_buffer[len - 1] = '\0';
    }

    if (validate_decimal_precision(input_buffer)) {
        printf("Valid decimal with precision 2\n");
    } else {
        printf("Invalid decimal\n");
    }

    return EXIT_SUCCESS;
}