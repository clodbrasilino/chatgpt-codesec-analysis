#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool string_starts_with_number(const char *string, const char *number)
{
    if (string == NULL || number == NULL || number[0] == '\0') {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t number_length = strlen(number);
    return strncmp(string, number, number_length) == 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char string[256];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char number[64];

    if (printf("Enter a string: ") < 0 || fflush(stdout) == EOF) {
        return 1;
    }

    if (fgets(string, sizeof(string), stdin) == NULL) {
        return 1;
    }

    if (strchr(string, '\n') == NULL) {
        int character;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((character = getchar()) != '\n' && character != EOF) {
        }
        if (character == EOF && ferror(stdin)) {
            return 1;
        }
    }
    string[strcspn(string, "\n")] = '\0';

    if (printf("Enter the starting number: ") < 0 || fflush(stdout) == EOF) {
        return 1;
    }

    if (fgets(number, sizeof(number), stdin) == NULL) {
        return 1;
    }

    if (strchr(number, '\n') == NULL) {
        int character;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((character = getchar()) != '\n' && character != EOF) {
        }
        if (character == EOF && ferror(stdin)) {
            return 1;
        }
    }
    number[strcspn(number, "\n")] = '\0';

    if (number[0] == '\0') {
        if (fprintf(stderr, "The number must not be empty.\n") < 0) {
            return 1;
        }
        return 1;
    }

    if (string_starts_with_number(string, number)) {
        if (printf("The string starts with %s.\n", number) < 0) {
            return 1;
        }
    } else {
        if (printf("The string does not start with %s.\n", number) < 0) {
            return 1;
        }
    }

    return 0;
}