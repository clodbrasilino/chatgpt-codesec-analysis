#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>

int64_t octagonal_number(int64_t n) {
    if (n > 3037000499LL) {
        errno = ERANGE;
        return -1;
    }
    return n * (3 * n - 2);
}

int main(void) {
    char buffer[128];
    char *endptr;
    int64_t n;
    int64_t result;
    size_t len;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    errno = 0;
    n = strtoimax(buffer, &endptr, 10);
    
    if (errno == ERANGE || endptr == buffer || *endptr != '\0') {
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
        fprintf(stderr, "Input too large: integer overflow\n");
        return EXIT_FAILURE;
    }
    
    printf("%" PRId64 "\n", result);
    
    return EXIT_SUCCESS;
}