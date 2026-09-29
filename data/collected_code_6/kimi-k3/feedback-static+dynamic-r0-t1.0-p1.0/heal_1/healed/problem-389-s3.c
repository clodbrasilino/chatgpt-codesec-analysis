#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long lucas(int n) {
    if (n == 0) return 2;
    if (n == 1) return 1;
    
    unsigned long long prev = 2;
    unsigned long long curr = 1;
    int i;
    
    for (i = 2; i <= n; i++) {
        if (ULLONG_MAX - curr < prev) {
            return 0;
        }
        unsigned long long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

int main(void) {
    char *input = NULL;
    size_t input_size = 0;
    ssize_t len;
    char *endptr;
    long val;
    int n;
    
    len = getline(&input, &input_size, stdin);
    if (len == -1) {
        free(input);
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtol(input, &endptr, 10);
    
    if (errno != 0 || endptr == input || val < 0 || val > INT_MAX) {
        free(input);
        return EXIT_FAILURE;
    }
    
    free(input);
    
    n = (int)val;
    printf("%llu\n", lucas(n));
    
    return EXIT_SUCCESS;
}