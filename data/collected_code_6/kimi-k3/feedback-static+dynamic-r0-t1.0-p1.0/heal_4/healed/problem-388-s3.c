#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

uint64_t highest_power_of_two(uint64_t n) {
    if (n == 0) {
        return 0;
    }
    
    n |= (n >> 1);
    n |= (n >> 2);
    n |= (n >> 4);
    n |= (n >> 8);
    n |= (n >> 16);
    n |= (n >> 32);
    
    return n - (n >> 1);
}

int main(void) {
    uint64_t n;
    char buffer[64];
    char *endptr;
    
    printf("Enter a positive integer: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    if (strlen(buffer) == 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    errno = 0;
    n = strtoull(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    uint64_t result = highest_power_of_two(n);
    printf("Highest power of 2 <= %" PRIu64 ": %" PRIu64 "\n", n, result);
    
    return 0;
}