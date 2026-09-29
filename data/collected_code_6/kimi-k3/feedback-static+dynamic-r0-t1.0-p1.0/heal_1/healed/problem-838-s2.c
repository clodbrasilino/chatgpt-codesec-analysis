#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minSwaps(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }
    
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    
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
    char str1[100];
    char str2[100];
    
    printf("Enter first binary string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter second binary string: ");
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    
    if (len1 > 0 && str1[len1 - 1] == '\n') {
        str1[len1 - 1] = '\0';
    }
    
    if (len2 > 0 && str2[len2 - 1] == '\n') {
        str2[len2 - 1] = '\0';
    }
    
    int result = minSwaps(str1, str2);
    
    if (result == -1) {
        printf("Cannot make strings equal (invalid input or different number of 1s)\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }
    
    return EXIT_SUCCESS;
}