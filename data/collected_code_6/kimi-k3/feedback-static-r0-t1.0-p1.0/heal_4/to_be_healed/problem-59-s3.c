#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 64

int64_t octagonal_number(int64_t n) {
    if (n > 3037000499LL) {
        errno = ERANGE;
        return -1;
    }
    return n * (3 * n - 2);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char *endptr;
    int64_t n;
    int64_t result;
    size_t len;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    len = strnlen(buffer, sizeof(buffer));
    /* Possible weaknesses found:
     *  Assuming that condition 'len==0' is not redundant
     */
    if (len == 0 || (len == sizeof(buffer) && buffer[len - 1] != '\n' && !feof(stdin))) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     *  Condition 'len>0' is always true [knownConditionTrueFalse]
     *  Condition 'len>0' is always true
     */
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    n = strtoimax(buffer, &endptr, 10);
    
    if (errno == ERANGE || endptr == buffer) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }
    
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Input must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    result = octagonal_number(n);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Input too large (overflow)\n");
        return EXIT_FAILURE;
    }
    
    printf("%" PRId64 "\n", result);
    
    return EXIT_SUCCESS;
}