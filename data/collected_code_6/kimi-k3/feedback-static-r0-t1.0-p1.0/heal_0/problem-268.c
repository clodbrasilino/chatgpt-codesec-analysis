#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

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
    char input[32];
    char *endptr;
    uint64_t n;
    uint64_t result;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
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