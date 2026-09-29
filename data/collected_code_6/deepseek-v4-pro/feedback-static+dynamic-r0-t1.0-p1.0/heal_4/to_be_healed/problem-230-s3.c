#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    char buffer[2048];
    char replacement;
    size_t len;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);

    if (len == 0) {
        fprintf(stderr, "Error: Empty input\n");
        return EXIT_FAILURE;
    }

    if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    printf("Enter replacement character: ");
    if (scanf(" %c", &replacement) != 1) {
        fprintf(stderr, "Error reading replacement character\n");
        return EXIT_FAILURE;
    }

    if (replacement == '\0') {
        fprintf(stderr, "Error: Replacement character cannot be null terminator\n");
        return EXIT_FAILURE;
    }

    replace_spaces(buffer, replacement);
    printf("Modified string: %s\n", buffer);

    return EXIT_SUCCESS;
}