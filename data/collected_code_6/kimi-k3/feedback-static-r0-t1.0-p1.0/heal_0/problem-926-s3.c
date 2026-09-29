#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

unsigned long long rencontres(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return 0;
    }
    
    unsigned long long prev_prev = 1;
    unsigned long long prev = 0;
    unsigned long long current = 0;
    
    for (int i = 2; i <= n; i++) {
        current = (unsigned long long)(i - 1) * (prev + prev_prev);
        prev_prev = prev;
        prev = current;
    }
    
    return current;
}

int main(void) {
    int n;
    char buffer[256];
    char *endptr;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    long val = strtol(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || *endptr != '\n' && *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (val < 0 || val > 20) {
        fprintf(stderr, "Input must be between 0 and 20\n");
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    printf("%llu\n", rencontres(n));
    
    return EXIT_SUCCESS;
}