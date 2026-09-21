#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

void replace_spaces(char *str, char replacement) {
    if (str == NULL) {
        fprintf(stderr, "Error: NULL pointer passed to replace_spaces\n");
        return;
    }

    if (replacement == '\0') {
        fprintf(stderr, "Error: Replacement character cannot be null terminator\n");
        return;
    }

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = replacement;
        }
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];
    char replacement;
    size_t len;
    int c;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(buffer, sizeof(buffer));

    if (len == 0 || buffer[0] == '\n') {
        fprintf(stderr, "Error: Empty input\n");
        return EXIT_FAILURE;
    }

    if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == EOF) {
                if (ferror(stdin)) {
                    fprintf(stderr, "Error reading from stdin\n");
                    return EXIT_FAILURE;
                }
            }
        }
    }

    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    if (len >= sizeof(buffer) - 1 && buffer[len] != '\0') {
        fprintf(stderr, "Error: String exceeds buffer capacity\n");
        return EXIT_FAILURE;
    }

    printf("Enter replacement character: ");
    errno = 0;
    if (scanf(" %c", &replacement) != 1) {
        if (errno != 0) {
            fprintf(stderr, "Error reading replacement character\n");
        } else {
            fprintf(stderr, "Error: Invalid input for replacement character\n");
        }
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == EOF && ferror(stdin)) {
                fprintf(stderr, "Error reading from stdin\n");
                return EXIT_FAILURE;
            }
        }
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c == EOF && ferror(stdin)) {
            fprintf(stderr, "Error reading from stdin\n");
            return EXIT_FAILURE;
        }
    }

    if (replacement == '\0') {
        fprintf(stderr, "Error: Replacement character cannot be null terminator\n");
        return EXIT_FAILURE;
    }

    replace_spaces(buffer, replacement);
    printf("Modified string: %s\n", buffer);

    return EXIT_SUCCESS;
}