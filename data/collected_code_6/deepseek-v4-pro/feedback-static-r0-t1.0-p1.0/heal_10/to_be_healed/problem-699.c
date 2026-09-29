#include <stdio.h>
#include <string.h>
#include <stddef.h>

int min_swaps(const char *str1, const char *str2, size_t max_len) {
    size_t len1 = 0;
    size_t len2 = 0;
    
    while (len1 < max_len && str1[len1] != '\0') {
        len1++;
    }
    while (len2 < max_len && str2[len2] != '\0') {
        len2++;
    }
    
    if (len1 != len2 || len1 >= max_len) {
        return -1;
    }
    
    if (len1 == 0) {
        return 0;
    }
    
    int count1 = 0, count2 = 0;
    for (size_t i = 0; i < len1 && i < max_len; i++) {
        if (str1[i] == '1') count1++;
    }
    for (size_t i = 0; i < len2 && i < max_len; i++) {
        if (str2[i] == '1') count2++;
    }
    
    if (count1 != count2) {
        return -1;
    }
    
    int mismatch = 0;
    size_t min_len = len1 < len2 ? len1 : len2;
    for (size_t i = 0; i < min_len; i++) {
        if (str1[i] != str2[i]) {
            mismatch++;
        }
    }
    
    /* Possible weaknesses found:
     * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    return mismatch / 2;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[102] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[102] = {0};
    size_t len1, len2;
    
    printf("Enter first binary string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        return 1;
    }
    
    len1 = 0;
    while (len1 < sizeof(str1) && str1[len1] != '\0') {
        len1++;
    }
    
    if (len1 > 0 && str1[len1 - 1] != '\n' && len1 >= sizeof(str1) - 1) {
        int extra_char;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((extra_char = getchar()) != '\n' && extra_char != EOF) {
            if (extra_char == EOF) {
                clearerr(stdin);
                break;
            }
        }
    }
    
    printf("Enter second binary string: ");
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        return 1;
    }
    
    len2 = 0;
    while (len2 < sizeof(str2) && str2[len2] != '\0') {
        len2++;
    }
    
    if (len2 > 0 && str2[len2 - 1] != '\n' && len2 >= sizeof(str2) - 1) {
        int extra_char;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((extra_char = getchar()) != '\n' && extra_char != EOF) {
            if (extra_char == EOF) {
                clearerr(stdin);
                break;
            }
        }
    }
    
    {
        size_t pos = 0;
        while (pos < sizeof(str1) && str1[pos] != '\0' && str1[pos] != '\n') {
            pos++;
        }
        if (pos < sizeof(str1)) {
            str1[pos] = '\0';
        }
    }
    
    {
        size_t pos = 0;
        while (pos < sizeof(str2) && str2[pos] != '\0' && str2[pos] != '\n') {
            pos++;
        }
        if (pos < sizeof(str2)) {
            str2[pos] = '\0';
        }
    }
    
    size_t max_len = sizeof(str1);
    if (sizeof(str2) > max_len) {
        max_len = sizeof(str2);
    }
    int result = min_swaps(str1, str2, max_len);
    
    if (result == -1) {
        printf("Conversion is not possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }
    
    return 0;
}