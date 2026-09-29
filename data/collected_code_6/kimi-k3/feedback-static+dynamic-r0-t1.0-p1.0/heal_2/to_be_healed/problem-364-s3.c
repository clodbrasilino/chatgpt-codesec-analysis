#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int countFlips(const char *str, size_t len) {
    if (str == NULL) {
        return -1;
    }
    
    if (len == 0) {
        return 0;
    }
    
    int count1 = 0;
    int count2 = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return -1;
        }
        
        char expected1 = (i % 2 == 0) ? '0' : '1';
        char expected2 = (i % 2 == 0) ? '1' : '0';
        
        if (str[i] != expected1) {
            count1++;
        }
        if (str[i] != expected2) {
            count2++;
        }
    }
    
    return (count1 < count2) ? count1 : count2;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    
    printf("Enter binary string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        fprintf(stderr, "Invalid input: empty string\n");
        return EXIT_FAILURE;
    }
    
    int result = countFlips(buffer, len);
    if (result < 0) {
        fprintf(stderr, "Invalid input: not a binary string\n");
        return EXIT_FAILURE;
    }
    
    printf("Number of flips required: %d\n", result);
    
    return EXIT_SUCCESS;
}