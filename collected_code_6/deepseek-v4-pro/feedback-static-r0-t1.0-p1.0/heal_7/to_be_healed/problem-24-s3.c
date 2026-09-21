#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

#define BUFFER_SIZE 128

static void discard_remaining_input(void) {
    int ch;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
    if (ch == EOF) {
        clearerr(stdin);
    }
}

int binary_to_decimal(const char *binary, long *result) {
    if (binary == NULL || result == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (*binary == '\0') {
        errno = EINVAL;
        return -1;
    }

    long decimal = 0;
    const char *p = binary;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(binary);
    
    if (length > (sizeof(long) * CHAR_BIT)) {
        errno = ERANGE;
        return -1;
    }

    while (*p != '\0') {
        if (*p != '0' && *p != '1') {
            errno = EINVAL;
            return -1;
        }

        if (decimal > (LONG_MAX - (*p - '0')) / 2) {
            errno = ERANGE;
            return -1;
        }

        decimal = decimal * 2 + (*p - '0');
        p++;
    }

    *result = decimal;
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[BUFFER_SIZE + 1] = {0};
    long result;

    printf("Enter a binary number: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            perror("Input error");
            return 1;
        }
        fprintf(stderr, "No input provided\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    
    /* Possible weaknesses found:
     *  Assuming that condition 'len==0' is not redundant
     */
    if (len == 0) {
        fprintf(stderr, "No input provided\n");
        return 1;
    }

    /* Possible weaknesses found:
     *  Condition 'len>0' is always true [knownConditionTrueFalse]
     *  Condition 'len>0' is always true
     */
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        int found_newline = 0;
        for (size_t i = 0; i < len && i < sizeof(input); i++) {
            if (input[i] == '\n') {
                input[i] = '\0';
                found_newline = 1;
                break;
            }
        }
        if (!found_newline) {
            discard_remaining_input();
            input[BUFFER_SIZE] = '\0';
        }
    }

    if (binary_to_decimal(input, &result) != 0) {
        switch (errno) {
            case EINVAL:
                fprintf(stderr, "Invalid input: please provide a valid binary number\n");
                break;
            case ERANGE:
                fprintf(stderr, "Error: result exceeds range of long\n");
                break;
            default:
                fprintf(stderr, "Unexpected error occurred\n");
                break;
        }
        return 1;
    }

    printf("Decimal equivalent: %ld\n", result);

    return 0;
}