#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 256

static void clear_input_stream(void) {
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF);
}

static int validate_and_parse(const char *buffer, int *result) {
    unsigned long long_val;
    char *endptr = NULL;
    
    errno = 0;
    long_val = strtoul(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || *endptr != '\0') {
        return 0;
    }
    
    if (long_val > (unsigned long)INT_MAX) {
        return 0;
    }
    
    *result = (int)long_val;
    return 1;
}

static void strip_newline(char *buffer) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 33, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 2 failed: expected 28, got <no output>
  */

int64_t countSetBits(int n) {
    int64_t count = 0;
    int totalBits = sizeof(int) * CHAR_BIT;
    int64_t power = 1;
    int64_t num = (int64_t)n + 1;
    
    for (int i = 0; i < totalBits; i++) {
        if (power > num) {
            break;
        }
        
        int64_t totalPairs = num / (power * 2);
        int64_t remainder = num % (power * 2);
        
        count += totalPairs * power;
        if (remainder > power) {
            count += remainder - power;
        }
        
        power <<= 1;
    }
    
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE + 1];
    int n;
    int overflow = 0;
    
    memset(buffer, 0, sizeof(buffer));
    
    printf("Enter a number: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (strchr(buffer, '\n') == NULL) {
        overflow = 1;
        clear_input_stream();
    }
    
    strip_newline(buffer);
    
    if (buffer[0] == '\0' || overflow) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (!validate_and_parse(buffer, &n)) {
        printf("Please enter a non-negative number within range\n");
        return 1;
    }
    
    printf("Total set bits from 1 to %d: %lld\n", n, (long long)countSetBits(n));
    
    return 0;
}