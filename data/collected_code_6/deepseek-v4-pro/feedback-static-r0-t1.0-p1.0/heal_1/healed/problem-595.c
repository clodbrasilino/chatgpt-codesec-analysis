#include <stdio.h>
#include <string.h>

int min_swaps_to_convert(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }
    
    size_t len1 = strnlen(s1, 1024);
    size_t len2 = strnlen(s2, 1024);
    
    if (len1 != len2 || len1 == 1024 || len2 == 1024) {
        return -1;
    }
    
    int count_ones_1 = 0, count_ones_2 = 0;
    int s1_zero_s2_one = 0;
    int s1_one_s2_zero = 0;
    
    for (size_t i = 0; i < len1; i++) {
        if (s1[i] == '1') count_ones_1++;
        if (s2[i] == '1') count_ones_2++;
        
        if (s1[i] != s2[i]) {
            if (s1[i] == '0' && s2[i] == '1') {
                s1_zero_s2_one++;
            } else if (s1[i] == '1' && s2[i] == '0') {
                s1_one_s2_zero++;
            } else {
                return -1;
            }
        }
    }
    
    if (count_ones_1 != count_ones_2) {
        return -1;
    }
    
    if (s1_zero_s2_one != s1_one_s2_zero) {
        return -1;
    }
    
    return s1_zero_s2_one;
}

int main(void) {
    const char *str1 = "1100";
    const char *str2 = "0011";
    
    int result = min_swaps_to_convert(str1, str2);
    
    if (result != -1) {
        printf("Minimum swaps required: %d\n", result);
    } else {
        printf("Conversion not possible\n");
    }
    
    const char *str3 = "1010";
    const char *str4 = "0101";
    result = min_swaps_to_convert(str3, str4);
    
    if (result != -1) {
        printf("Minimum swaps required: %d\n", result);
    } else {
        printf("Conversion not possible\n");
    }
    
    const char *str5 = "110";
    const char *str6 = "001";
    result = min_swaps_to_convert(str5, str6);
    
    if (result != -1) {
        printf("Minimum swaps required: %d\n", result);
    } else {
        printf("Conversion not possible\n");
    }
    
    return 0;
}