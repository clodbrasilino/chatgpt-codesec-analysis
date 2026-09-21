#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int64_t sum_odd_natural(int64_t l, int64_t r) {
    if (l > r || r < 1) {
        return 0;
    }
    
    int64_t start = (l < 1) ? 1 : l;
    int64_t first_odd = (start % 2 == 0) ? start + 1 : start;
    
    if (first_odd > r) {
        return 0;
    }
    
    int64_t last_odd = (r % 2 == 0) ? r - 1 : r;
    int64_t count = (last_odd - first_odd) / 2 + 1;
    
    return count * (first_odd + last_odd) / 2;
}

int main(void) {
    char buffer[256];
    int64_t l, r;
    char *endptr;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    errno = 0;
    l = strtoimax(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer) {
        return 1;
    }
    
    while (*endptr == ' ' || *endptr == '\t') {
        endptr++;
    }
    
    errno = 0;
    r = strtoimax(endptr, &endptr, 10);
    if (errno != 0) {
        return 1;
    }
    
    printf("%" PRId64 "\n", sum_odd_natural(l, r));
    
    return 0;
}