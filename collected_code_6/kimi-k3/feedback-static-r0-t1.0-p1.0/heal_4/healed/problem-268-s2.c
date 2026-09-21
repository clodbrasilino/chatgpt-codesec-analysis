#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>

uint64_t star_number(uint64_t n) {
    return 6 * n * (n - 1) + 1;
}

int main(void) {
    char buffer[32];
    uint64_t n;
    char *endptr;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    errno = 0;
    n = strtoull(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        return 1;
    }
    
    if (n == 0) {
        return 1;
    }
    
    printf("%" PRIu64 "\n", star_number(n));
    
    return 0;
}