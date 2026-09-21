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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    int64_t l, r;
    char *endptr;
    size_t len;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    len = 0;
    while (len < sizeof(buffer) - 1 && buffer[len] != '\0' && buffer[len] != '\n') {
        len++;
    }
    /* Possible weaknesses found:
     *  Assignment 'buffer[len]='\0'', assigned value is 0
     */
    buffer[len] = '\0';
    
    /* Possible weaknesses found:
     *  Condition 'buffer[len]!='\n'' is always true
     *  Condition 'buffer[len]!='\n'' is always true [knownConditionTrueFalse]
     */
    if (len == sizeof(buffer) - 1 && buffer[len] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
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