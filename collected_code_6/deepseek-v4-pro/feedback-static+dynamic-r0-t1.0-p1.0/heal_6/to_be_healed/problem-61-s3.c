#include <stdio.h>
#include <string.h>
#include <stddef.h>

int countSubstrings(const char *str, size_t max_len) {
    size_t n = 0;
    while (n < max_len && str[n] != '\0') {
        n++;
    }
    
    int count = 0;
    
    for (size_t i = 0; i < n; i++) {
        int sum = 0;
        for (size_t j = i; j < n; j++) {
            sum += str[j] - '0';
            size_t len = j - i + 1;
            if (sum == (int)len) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[1001];
    
    if (fgets(str, sizeof(str), stdin) != NULL) {
        str[sizeof(str) - 1] = '\0';
        size_t len = 0;
        while (len < sizeof(str) && str[len] != '\0') {
            len++;
        }
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
            /* Possible weaknesses found:
             *  Variable 'len' is assigned a value that is never used. [unreadVariable]
             */
            len--;
        }
        printf("%d\n", countSubstrings(str, sizeof(str)));
    }
    
    return 0;
}