#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minSwapsToEqual(char *s1, char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }
    
    size_t len1 = strnlen(s1, 1000);
    size_t len2 = strnlen(s2, 1000);
    
    if (len1 >= 1000 || len2 >= 1000) {
        return -1;
    }
    
    if (len1 != len2) {
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
    char s1[1001], s2[1001];
    
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    while (scanf("%1000s %1000s", s1, s2) == 2) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len1 = strlen(s1);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len2 = strlen(s2);
        
        if (len1 > 1000 || len2 > 1000) {
            printf("-1\n");
            continue;
        }
        
        s1[1000] = '\0';
        s2[1000] = '\0';
        
        int result = minSwapsToEqual(s1, s2);
        printf("%d\n", result);
    }
    
    return 0;
}