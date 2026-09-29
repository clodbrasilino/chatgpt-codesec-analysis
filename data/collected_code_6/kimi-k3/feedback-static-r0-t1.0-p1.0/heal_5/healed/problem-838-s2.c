#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int minSwaps(const char *str1, const char *str2, size_t max_len) {
    if (str1 == NULL || str2 == NULL || max_len == 0) {
        return -1;
    }
    
    size_t len1 = strnlen(str1, max_len);
    size_t len2 = strnlen(str2, max_len);
    
    if (len1 == max_len || len2 == max_len) {
        return -1;
    }
    
    if (len1 != len2) {
        return -1;
    }
    
    int count1 = 0;
    int count2 = 0;
    
    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != '0' && str1[i] != '1') {
            return -1;
        }
        if (str2[i] != '0' && str2[i] != '1') {
            return -1;
        }
        
        if (str1[i] == '1') {
            count1++;
        }
        if (str2[i] == '1') {
            count2++;
        }
    }
    
    if (count1 != count2) {
        return -1;
    }
    
    int mismatches = 0;
    
    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != str2[i]) {
            mismatches++;
        }
    }
    
    return mismatches / 2;
}

int main(void) {
    char *str1 = NULL;
    char *str2 = NULL;
    size_t size1 = 0;
    size_t size2 = 0;
    ssize_t len1;
    ssize_t len2;
    
    printf("Enter first binary string: ");
    len1 = getline(&str1, &size1, stdin);
    if (len1 == -1) {
        fprintf(stderr, "Error reading input\n");
        free(str1);
        return EXIT_FAILURE;
    }
    
    printf("Enter second binary string: ");
    len2 = getline(&str2, &size2, stdin);
    if (len2 == -1) {
        fprintf(stderr, "Error reading input\n");
        free(str1);
        free(str2);
        return EXIT_FAILURE;
    }
    
    if (len1 > 0 && str1[len1 - 1] == '\n') {
        str1[len1 - 1] = '\0';
        len1--;
    }
    
    if (len2 > 0 && str2[len2 - 1] == '\n') {
        str2[len2 - 1] = '\0';
        len2--;
    }
    
    int result = minSwaps(str1, str2, (size_t)len1 + 1);
    
    if (result == -1) {
        printf("Cannot make strings equal (invalid input or different number of 1s)\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }
    
    free(str1);
    free(str2);
    
    return EXIT_SUCCESS;
}