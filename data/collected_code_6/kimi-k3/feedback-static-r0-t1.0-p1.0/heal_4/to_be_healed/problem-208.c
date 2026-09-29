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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[256];

    printf("Enter a decimal number: ");

    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (strchr(input_buffer, '\n') == NULL) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    input_buffer[strcspn(input_buffer, "\n")] = '\0';

    if (validate_decimal_precision(input_buffer)) {
        printf("Valid decimal with precision 2\n");
    } else {
        printf("Invalid decimal\n");
    }

    return EXIT_SUCCESS;
}