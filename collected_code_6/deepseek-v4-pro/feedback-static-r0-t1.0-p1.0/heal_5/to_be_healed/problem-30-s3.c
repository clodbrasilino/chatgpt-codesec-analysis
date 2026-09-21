#include <stdio.h>
#include <string.h>
#include <errno.h>

int count_substrings_same_start_end(const char *str) {
    int count = 0;
    int freq[256] = {0};
    size_t len;
    
    if (str == NULL) {
        return 0;
    }
    
    len = strnlen(str, 1000);
    if (len == 1000 && str[999] != '\0') {
        return 0;
    }
    
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
    char input[2048];
    size_t len;
    size_t max_len = sizeof(input) - 1;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    input[max_len] = '\0';
    
    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        int c;
        int consumed = 0;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
            consumed++;
            if (consumed > 4096) {
                break;
            }
        }
        if (c == EOF && ferror(stdin)) {
            fprintf(stderr, "Error reading input\n");
            return 1;
        }
    }
    
    if (input[0] == '\0') {
        printf("Total substrings: 0\n");
        return 0;
    }
    
    int result = count_substrings_same_start_end(input);
    printf("Total substrings: %d\n", result);
    
    return 0;
}