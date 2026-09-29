#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_first_and_last(char *str, char target)
{
    char *first;
    char *last;

    if (str == NULL) {
        return -1;
    }

    first = strchr(str, target);
    if (first == NULL) {
        return 0;
    }

    last = strrchr(str, target);

    if (first == last) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(first, first + 1, strlen(first + 1) + 1);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    memmove(last, last + 1, strlen(last + 1) + 1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    memmove(first, first + 1, strlen(first + 1) + 1);

    return 2;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char target_input[3];
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(input);
    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    } else if (length == sizeof input - 1) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        if (ch != '\n') {
            return EXIT_FAILURE;
        }
    }

    if (fgets(target_input, sizeof target_input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (target_input[0] == '\n' || target_input[0] == '\0') {
        return EXIT_FAILURE;
    }

    if (target_input[1] != '\n' && target_input[1] != '\0') {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        return EXIT_FAILURE;
    }

    if (remove_first_and_last(input, target_input[0]) < 0) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", input) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}