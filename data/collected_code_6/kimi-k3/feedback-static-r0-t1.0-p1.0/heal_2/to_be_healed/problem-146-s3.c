#include <stdio.h>
#include <string.h>
#include <stddef.h>

int calculate_ascii_sum(const char *str, size_t max_len) {
    int sum = 0;
    size_t i;
    size_t len;
    
    if (str == NULL) {
        return -1;
    }
    
    len = strnlen(str, max_len);
    
    for (i = 0; i < len; i++) {
        sum += (int)str[i];
    }
    
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    int result;
    
    printf("Enter a string: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    result = calculate_ascii_sum(input, sizeof(input));
    
    if (result == -1) {
        fprintf(stderr, "Error: Invalid string\n");
        return 1;
    }
    
    printf("Total ASCII value: %d\n", result);
    
    return 0;
}