#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_substrings(const char *str) {
    int count = 0;
    int freq[256] = {0};
    
    if (str == NULL) {
        return 0;
    }
    
    size_t len = strnlen(str, 1000);
    
    for (size_t i = 0; i < len; i++) {
        freq[(unsigned char)str[i]]++;
    }
    
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            count += freq[i] * (freq[i] + 1) / 2;
        }
    }
    
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1001];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    int result = count_substrings(input);
    printf("Number of substrings: %d\n", result);
    
    return 0;
}