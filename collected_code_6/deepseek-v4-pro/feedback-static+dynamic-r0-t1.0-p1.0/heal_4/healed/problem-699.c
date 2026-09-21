#include <stdio.h>
#include <string.h>

int min_swaps(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    size_t len1 = strnlen(str1, 101);
    size_t len2 = strnlen(str2, 101);
    
    if (len1 != len2 || len1 == 101 || len2 == 101) {
        return -1;
    }
    
    size_t len = len1;
    
    int count1 = 0, count2 = 0;
    for (size_t i = 0; i < len; i++) {
        if (str1[i] == '1') count1++;
        if (str2[i] == '1') count2++;
    }
    
    if (count1 != count2) {
        return -1;
    }
    
    int mismatch = 0;
    for (size_t i = 0; i < len; i++) {
        if (str1[i] != str2[i]) {
            mismatch++;
        }
    }
    
    return mismatch / 2;
}

int main(void) {
    char str1[102] = {0};
    char str2[102] = {0};
    
    printf("Enter first binary string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        return 1;
    }
    
    printf("Enter second binary string: ");
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        return 1;
    }
    
    str1[strcspn(str1, "\n")] = '\0';
    str2[strcspn(str2, "\n")] = '\0';
    
    size_t actual_len1 = strnlen(str1, 101);
    size_t actual_len2 = strnlen(str2, 101);
    
    if (actual_len1 > 100 || actual_len2 > 100) {
        printf("Conversion is not possible\n");
        return 0;
    }
    
    int result = min_swaps(str1, str2);
    
    if (result == -1) {
        printf("Conversion is not possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }
    
    return 0;
}