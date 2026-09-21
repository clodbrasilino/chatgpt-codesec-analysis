#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static uint64_t sum_of_squares(uint64_t n)
{
    if (n == 0) {
        return 0;
    }
    
    if (n > 1862644) {
        errno = ERANGE;
        return UINT64_MAX;
    }
    
    return (n * (n + 1) * (2 * n + 1)) / 6;
}

static int parse_uint64(const char *str, uint64_t *result)
{
    char *endptr;
    unsigned long long value;
    
    if (str == NULL || *str == '\0') {
        return -1;
    }
    
    while (isspace((unsigned char)*str)) {
        str++;
    }
    
    if (*str == '\0') {
        return -1;
    }
    
    errno = 0;
    value = strtoull(str, &endptr, 10);
    
    if (errno == ERANGE) {
        return -1;
    }
    
    if (endptr == str) {
        return -1;
    }
    
    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }
    
    if (*endptr != '\0') {
        return -1;
    }
    
    if (value > UINT64_MAX) {
        return -1;
    }
    
    *result = (uint64_t)value;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[64];
    uint64_t n;
    uint64_t result;
    
    printf("Enter a positive integer: ");
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    if (parse_uint64(input_buffer, &n) != 0) {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    errno = 0;
    result = sum_of_squares(n);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Error: Input too large, result would overflow\n");
        return 1;
    }
    
    printf("Sum of squares: %" PRIu64 "\n", result);
    
    return 0;
}