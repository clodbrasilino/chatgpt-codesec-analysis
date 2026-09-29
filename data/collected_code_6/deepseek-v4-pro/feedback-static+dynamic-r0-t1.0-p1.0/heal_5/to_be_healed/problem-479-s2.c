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
    char buffer[256];
    char *endptr;
    long input;
    int number;
    size_t len;
    size_t i;

    printf("Enter an integer: ");
    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(buffer, sizeof(buffer));
    if (len == sizeof(buffer) && buffer[sizeof(buffer) - 1] != '\0') {
        buffer[sizeof(buffer) - 1] = '\0';
        len = sizeof(buffer) - 1;
    }

    if (len > 0 && buffer[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == EOF) {
                clearerr(stdin);
            }
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    i = 0;
    while (i < len && isspace((unsigned char)buffer[i])) {
        i++;
    }
    if (i >= len) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtol(buffer, &endptr, 10);

    if (errno == ERANGE || input < (long)INT_MIN || input > (long)INT_MAX) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }

    if (endptr == buffer) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
        endptr++;
    }

    number = (int)input;
    printf("%d\n", first_digit(number));
    return EXIT_SUCCESS;
}