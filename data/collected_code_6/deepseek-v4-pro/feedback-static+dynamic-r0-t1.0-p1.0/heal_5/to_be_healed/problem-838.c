#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minSwapsToEqual(const char *s1, const char *s2) {
    if (!s1 || !s2) {
        return -1;
    }
    
    size_t len1 = strnlen(s1, 1001);
    size_t len2 = strnlen(s2, 1001);
    
    if (len1 != len2) {
        return -1;
    }
    
    if (len1 > 1000) {
        return -1;
    }
    
    int len = (int)len1;
    int count1 = 0, count2 = 0;
    int diff1 = 0, diff2 = 0;
    
    for (int i = 0; i < len; i++) {
        if (s1[i] == '1') count1++;
        if (s2[i] == '1') count2++;
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') diff1++;
            else diff2++;
        }
    }
    
    if (count1 != count2) {
        return -1;
    }
    
    if (diff1 == 0 && diff2 == 0) {
        return 0;
    }
    
    if (diff1 % 2 == 1 || diff2 % 2 == 1) {
        return -1;
    }
    
    return (diff1 / 2) + (diff2 / 2) + (diff1 % 2) * 2;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s1[1002];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s2[1002];
    
    while (fgets(s1, (int)sizeof(s1), stdin) && fgets(s2, (int)sizeof(s2), stdin)) {
        size_t len1 = strnlen(s1, sizeof(s1));
        size_t len2 = strnlen(s2, sizeof(s2));
        
        if (len1 > 0 && s1[len1 - 1] == '\n') {
            s1[len1 - 1] = '\0';
            len1--;
        } else if (len1 == sizeof(s1) - 1) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF);
        }
        
        if (len2 > 0 && s2[len2 - 1] == '\n') {
            s2[len2 - 1] = '\0';
            len2--;
        } else if (len2 == sizeof(s2) - 1) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF);
        }
        
        if (len1 > 1000 || len2 > 1000) {
            printf("-1\n");
            continue;
        }
        
        int result = minSwapsToEqual(s1, s2);
        printf("%d\n", result);
    }
    
    return 0;
}