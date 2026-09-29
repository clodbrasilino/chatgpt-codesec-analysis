#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_swaps(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }
    
    size_t len1 = strnlen(s1, 1001);
    size_t len2 = strnlen(s2, 1001);
    
    if (len1 >= 1000 || len2 >= 1000) return -1;
    if (len1 != len2) return -1;
    
    for (size_t i = 0; i < len1; i++) {
        if (s1[i] != '0' && s1[i] != '1') return -1;
        if (s2[i] != '0' && s2[i] != '1') return -1;
    }
    
    int count1_0 = 0, count1_1 = 0;
    int count2_0 = 0, count2_1 = 0;
    
    for (size_t i = 0; i < len1; i++) {
        if (s1[i] == '0') count1_0++;
        else count1_1++;
        
        if (s2[i] == '0') count2_0++;
        else count2_1++;
    }
    
    if (count1_0 != count2_0 || count1_1 != count2_1) {
        return -1;
    }
    
    int mismatch_0_to_1 = 0;
    int mismatch_1_to_0 = 0;
    
    for (size_t i = 0; i < len1; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '0' && s2[i] == '1') {
                mismatch_0_to_1++;
            } else if (s1[i] == '1' && s2[i] == '0') {
                mismatch_1_to_0++;
            }
        }
    }
    
    if (mismatch_0_to_1 != mismatch_1_to_0) {
        return -1;
    }
    
    return mismatch_0_to_1;
}

int main(void) {
    char str1[1001] = {0};
    char str2[1001] = {0};
    size_t len1, len2;
    size_t max_input = sizeof(str1) - 1;

    printf("Enter first binary string: ");
    if (fgets(str1, (int)sizeof(str1), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    if (str1[max_input] != '\0') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Input too long\n");
        return 1;
    }
    
    len1 = strnlen(str1, sizeof(str1));
    if (len1 > 0 && str1[len1 - 1] == '\n') {
        str1[len1 - 1] = '\0';
        len1--;
    }

    printf("Enter second binary string: ");
    if (fgets(str2, (int)sizeof(str2), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    if (str2[max_input] != '\0') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Input too long\n");
        return 1;
    }
    
    len2 = strnlen(str2, sizeof(str2));
    if (len2 > 0 && str2[len2 - 1] == '\n') {
        str2[len2 - 1] = '\0';
        len2--;
    }
    
    if (len1 != len2) {
        printf("Conversion not possible\n");
        return 1;
    }
    
    int result = min_swaps(str1, str2);
    
    if (result == -1) {
        printf("Conversion not possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }
    
    return 0;
}