#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 64

int64_t maxVolume(int64_t S) {
    if (S < 3) {
        return 0;
    }
    
    int64_t a = S / 3;
    int64_t b = (S - a) / 2;
    int64_t c = S - a - b;
    
    /* Possible weaknesses found:
     *  Assuming that condition 'b<1' is not redundant
     *  Assuming that condition 'c<1' is not redundant
     */
    if (a < 1 || b < 1 || c < 1) {
        return 0;
    }
    
    /* Possible weaknesses found:
     *  Condition 'b>0' is always true [knownConditionTrueFalse]
     *  Condition 'b>0' is always true
     *  Assuming condition is false
     */
    if (b > 0 && a > INT64_MAX / b) {
        return 0;
    }
    
    int64_t ab = a * b;
    
    /* Possible weaknesses found:
     *  Condition 'c>0' is always true [knownConditionTrueFalse]
     *  Condition 'c>0' is always true
     */
    if (c > 0 && ab > INT64_MAX / c) {
        return 0;
    }
    
    return ab * c;
}

int main(void) {
    int64_t sumSides;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char *endptr;
    size_t len;
    
    printf("Enter sum of sides: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    if (len >= sizeof(buffer) - 1 && buffer[sizeof(buffer) - 1] != '\0') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {}
        fprintf(stderr, "Input too long\n");
        return 1;
    }
    
    errno = 0;
    sumSides = strtoll(buffer, &endptr, 10);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Value out of range\n");
        return 1;
    }
    
    if (endptr == buffer || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (sumSides < 3) {
        fprintf(stderr, "Sum must be at least 3\n");
        return 1;
    }
    
    int64_t volume = maxVolume(sumSides);
    printf("Maximum volume: %" PRId64 "\n", volume);
    
    return 0;
}