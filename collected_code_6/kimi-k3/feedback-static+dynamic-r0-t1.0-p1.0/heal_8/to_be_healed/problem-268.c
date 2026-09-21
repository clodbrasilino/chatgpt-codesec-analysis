#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 64

uint64_t star_number(uint64_t n) {
    if (n == 0) {
        return 0;
    }
    if (n > 6074000999ULL) {
        return UINT64_MAX;
    }
    return 6 * n * (n - 1) + 1;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_SIZE];
    char *endptr;
    uint64_t n;
    uint64_t result;
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int c;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    len = strnlen(input, sizeof(input));
    
    if (len == sizeof(input) - 1 && input[len - 1] != '\n' && !feof(stdin)) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    errno = 0;
    n = strtoull(input, &endptr, 10);
    
    if (errno == ERANGE || endptr == input || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    result = star_number(n);
    
    if (result == UINT64_MAX && n != 0) {
        fprintf(stderr, "Result overflow\n");
        return 1;
    }
    
    printf("%" PRIu64 "\n", result);
    
    return 0;
}