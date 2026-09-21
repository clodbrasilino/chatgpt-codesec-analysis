#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

int validate_string(const char *input) {
    regex_t regex;
    int ret;
    int result = 0;

    if (input == NULL) {
        return 0;
    }

    ret = regcomp(&regex, "^[a-zA-Z0-9]+$", REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, input, 0, NULL, 0);
    if (ret == 0) {
        result = 1;
    } else if (ret != REG_NOMATCH) {
        result = 0;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    int validation_result;
    size_t len;
    int c;

    printf("Enter a string to validate: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strcspn(buffer, "\n");
    
    if (buffer[len] == '\n') {
        buffer[len] = '\0';
    } else if (len == sizeof(buffer) - 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Error: Input too long\n");
        return EXIT_FAILURE;
    } else {
        buffer[len] = '\0';
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