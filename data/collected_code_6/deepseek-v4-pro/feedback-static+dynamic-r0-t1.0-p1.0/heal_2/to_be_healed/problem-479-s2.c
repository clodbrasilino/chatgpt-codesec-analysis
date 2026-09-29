#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 4, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  */

int first_digit(int num) {
    if (num == INT_MIN) {
        return 2;
    }
    if (num < 0) {
        num = -num;
    }
    while (num >= 10) {
        num /= 10;
    }
    return num;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    long input;
    int number;
    size_t len;

    printf("Enter an integer: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {}
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    if (len == 1 && buffer[0] == '\n') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    {
        size_t i = 0;
        while (i < len && isspace((unsigned char)buffer[i])) {
            i++;
        }
        if (i == len || buffer[i] == '\n') {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    input = strtol(buffer, &endptr, 10);

    if (errno == ERANGE || input < INT_MIN || input > INT_MAX) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }

    while (*endptr == ' ' || *endptr == '\t') {
        endptr++;
    }
    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    number = (int)input;
    printf("First digit: %d\n", first_digit(number));
    return EXIT_SUCCESS;
}