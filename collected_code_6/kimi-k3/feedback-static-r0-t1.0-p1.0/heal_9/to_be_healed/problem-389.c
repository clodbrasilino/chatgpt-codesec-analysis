#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

unsigned long long lucas(unsigned int n) {
    unsigned long long a = 2, b = 1;
    unsigned int i;
    
    if (n == 0) {
        return 2;
    }
    
    for (i = 1; i < n; i++) {
        unsigned long long temp = a + b;
        a = b;
        b = temp;
    }
    
    return b;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *endptr;
    long value;
    unsigned int n;
    size_t len;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    len = strnlen(buffer, sizeof(buffer));
    if (len == 0) {
        return EXIT_FAILURE;
    }
    
    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        return EXIT_FAILURE;
    }
    
    errno = 0;
    value = strtol(buffer, &endptr, 10);
    
    if (errno == ERANGE || endptr == buffer || value < 0 || value > 93) {
        return EXIT_FAILURE;
    }
    
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }
    
    n = (unsigned int)value;
    printf("%llu\n", lucas(n));
    
    return EXIT_SUCCESS;
}