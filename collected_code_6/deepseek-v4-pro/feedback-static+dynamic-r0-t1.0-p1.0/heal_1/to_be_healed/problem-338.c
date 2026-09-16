#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_substrings_same_ends(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int len = strlen(str);
    if (len == 0) {
        return 0;
    }
    
    int *count = (int *)calloc(256, sizeof(int));
    if (count == NULL) {
        return 0;
    }
    
    for (int i = 0; i < len; i++) {
        count[(unsigned char)str[i]]++;
    }
    
    int result = 0;
    for (int i = 0; i < 256; i++) {
        if (count[i] > 1) {
            result += (count[i] * (count[i] - 1)) / 2;
        }
        result += count[i];
    }
    
    free(count);
    return result;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'str1' can be declared as const array [constVariable]
     */
    char str1[] = "abcab";
    /* Possible weaknesses found:
     *  Variable 'str2' can be declared as const array [constVariable]
     */
    char str2[] = "aba";
    /* Possible weaknesses found:
     *  Variable 'str3' can be declared as const array [constVariable]
     */
    char str3[] = "aaaa";
    /* Possible weaknesses found:
     *  Variable 'str4' can be declared as const array [constVariable]
     */
    char str4[] = "";
    
    printf("%d\n", count_substrings_same_ends(str1));
    printf("%d\n", count_substrings_same_ends(str2));
    printf("%d\n", count_substrings_same_ends(str3));
    printf("%d\n", count_substrings_same_ends(str4));
    
    return 0;
}