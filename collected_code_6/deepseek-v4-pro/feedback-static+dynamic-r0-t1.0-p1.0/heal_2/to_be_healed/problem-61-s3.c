#include <stdio.h>
#include <string.h>
#include <stddef.h>

int countSubstrings(const char *str) {
    int n = 0;
    while (str[n] != '\0') {
        if (n >= 999) break;
        n++;
    }
    
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += str[j] - '0';
            int len = j - i + 1;
            if (sum == len) {
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
        size_t newline_pos = strcspn(str, "\n");
        if (newline_pos < sizeof(str)) {
            str[newline_pos] = '\0';
        }
        printf("%d\n", countSubstrings(str));
    }
    
    return 0;
}