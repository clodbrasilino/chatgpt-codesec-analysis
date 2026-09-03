#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_swaps_to_convert(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }
    
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    
    if (len1 != len2) {
        return -1;
    }
    
    int count1_ones = 0;
    int count2_ones = 0;
    int mismatched_positions = 0;
    
    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != '0' && str1[i] != '1') {
            return -1;
        }
        if (str2[i] != '0' && str2[i] != '1') {
            return -1;
        }
        
        if (str1[i] == '1') {
            count1_ones++;
        }
        if (str2[i] == '1') {
            count2_ones++;
        }
        
        if (str1[i] != str2[i]) {
            mismatched_positions++;
        }
    }
    
    if (count1_ones != count2_ones) {
        return -1;
    }
    
    return mismatched_positions / 2;
}

int main(void) {
    const char *str1 = "1100";
    const char *str2 = "0011";
    
    int result = min_swaps_to_convert(str1, str2);
    
    if (result == -1) {
        printf("Conversion not possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }
    
    const char *str3 = "1010";
    const char *str4 = "0101";
    
    result = min_swaps_to_convert(str3, str4);
    
    if (result == -1) {
        printf("Conversion not possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }
    
    const char *str5 = "111";
    const char *str6 = "000";
    
    result = min_swaps_to_convert(str5, str6);
    
    if (result == -1) {
        printf("Conversion not possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }
    
    const char *str7 = "110";
    const char *str8 = "101";
    
    result = min_swaps_to_convert(str7, str8);
    
    if (result == -1) {
        printf("Conversion not possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }
    
    return 0;
}