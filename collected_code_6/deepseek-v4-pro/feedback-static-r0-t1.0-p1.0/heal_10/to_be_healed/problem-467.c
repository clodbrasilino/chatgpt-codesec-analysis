#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

void decimal_to_octal(unsigned int decimal, char *octal, size_t size) {
    /* Possible weaknesses found:
     *  Assuming that condition 'size==0' is not redundant
     */
    if (size == 0) {
        return;
    }

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (decimal == 0) {
        if (size < 2) {
            octal[0] = '\0';
            return;
        }
        octal[0] = '0';
        octal[1] = '\0';
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[12];
    size_t temp_size = sizeof(temp);
    size_t index = 0;

    while (decimal > 0 && index < temp_size - 1) {
        temp[index++] = (decimal % 8) + '0';
        decimal /= 8;
    }
    temp[index] = '\0';

    if (index >= size) {
        /* Possible weaknesses found:
         *  Condition 'size>0' is always true [knownConditionTrueFalse]
         *  Condition 'size>0' is always true
         */
        if (size > 0) {
            octal[0] = '\0';
        }
        return;
    }

    size_t result_index = 0;
    size_t i = index;
    while (i > 0 && result_index < size - 1) {
        octal[result_index++] = temp[--i];
    }
    octal[result_index] = '\0';
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    long decimal;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char octal[12];
    char *endptr;
    size_t input_len;

    printf("Enter a decimal number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input_len = strcspn(input, "\n");
    if (input_len >= sizeof(input) - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    input[input_len] = '\0';

    if (input_len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    decimal = strtol(input, &endptr, 10);

    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }

    if (endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (decimal < 0 || decimal > UINT_MAX) {
        fprintf(stderr, "Number out of range or negative\n");
        return EXIT_FAILURE;
    }

    decimal_to_octal((unsigned int)decimal, octal, sizeof(octal));
    printf("Octal: %s\n", octal);

    return EXIT_SUCCESS;
}