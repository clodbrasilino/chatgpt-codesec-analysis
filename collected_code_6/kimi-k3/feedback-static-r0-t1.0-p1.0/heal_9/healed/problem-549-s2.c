#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

uint64_t sum_fifth_power_odd(uint32_t n) {
    uint64_t sum = 0;
    uint32_t i;
    
    for (i = 0; i < n; i++) {
        uint64_t odd = 2ULL * i + 1ULL;
        uint64_t power = odd * odd * odd * odd * odd;
        
        if (UINT64_MAX - sum < power) {
            return UINT64_MAX;
        }
        sum += power;
    }
    
    return sum;
}

int main(void) {
    uint32_t n;
    uint64_t result;
    char buffer[64];
    char *endptr;
    unsigned long temp;
    size_t len;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    len = strnlen(buffer, sizeof(buffer));
    
    if (len == 0) {
        return 1;
    }
    
    if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 1;
    }
    
    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        return 1;
    }
    
    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)buffer[i])) {
            return 1;
        }
    }
    
    errno = 0;
    temp = strtoul(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || *endptr != '\0' || temp > UINT32_MAX) {
        return 1;
    }
    
    n = (uint32_t)temp;
    
    result = sum_fifth_power_odd(n);
    printf("%" PRIu64 "\n", result);
    
    return 0;
}