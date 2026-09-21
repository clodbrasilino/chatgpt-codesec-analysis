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
    char buffer[256];
    char *endptr;
    long value;
    unsigned int n;
    size_t len;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    len = strnlen(buffer, sizeof(buffer));
    
    if (len == sizeof(buffer)) {
        return EXIT_FAILURE;
    }
    
    errno = 0;
    value = strtol(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || value < 0 || value > 93) {
        return EXIT_FAILURE;
    }
    
    if (*endptr != '\n' && *endptr != '\0') {
        return EXIT_FAILURE;
    }
    
    n = (unsigned int)value;
    printf("%llu\n", lucas(n));
    
    return EXIT_SUCCESS;
}