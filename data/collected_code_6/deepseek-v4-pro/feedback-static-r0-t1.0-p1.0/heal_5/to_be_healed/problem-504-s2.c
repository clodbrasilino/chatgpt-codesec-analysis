#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <inttypes.h>

unsigned long long cube_sum_natural_numbers(int n) {
    if (n < 0) {
        return 0;
    }
    
    unsigned long long nn = (unsigned long long)n;
    unsigned long long sum = (nn * nn * (nn + 1) * (nn + 1)) / 4;
    
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    char *endptr;
    long n;
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int c;
    
    printf("Enter a positive integer: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    /* Possible weaknesses found:
     *  Assuming that condition 'input[len-1]!='\n'' is not redundant
     *  Assuming that condition 'len==0' is not redundant
     */
    if (len == 0 || input[len - 1] != '\n') {
        if (len == sizeof(input) - 1 && input[len - 1] != '\n') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
            }
        }
        fprintf(stderr, "Input too long or empty\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     *  Condition 'input[len-1]=='\n'' is always true [knownConditionTrueFalse]
     *  Condition 'input[len-1]=='\n'' is always true
     *  Condition 'len>0' is always true [knownConditionTrueFalse]
     *  Condition 'len>0' is always true
     */
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        fprintf(stderr, "Empty input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    n = strtol(input, &endptr, 10);
    
    if (errno == ERANGE || n < 0 || n > INT_MAX) {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = cube_sum_natural_numbers((int)n);
    printf("Cube sum of first %d natural numbers: %llu\n", (int)n, result);
    
    return EXIT_SUCCESS;
}