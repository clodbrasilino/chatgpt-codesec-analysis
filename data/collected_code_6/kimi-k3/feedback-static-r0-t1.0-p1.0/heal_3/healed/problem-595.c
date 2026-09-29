#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_LEN 1000

int minSwaps(const char *str1, size_t len1, const char *str2, size_t len2) {
    if (len1 != len2) {
        return -1;
    }

    int count1 = 0, count2 = 0;
    for (size_t i = 0; i < len1; i++) {
        if (str1[i] == '1') count1++;
        if (str2[i] == '1') count2++;
    }

    if (count1 != count2) {
        return -1;
    }

    int swaps = 0;
    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != str2[i]) {
            swaps++;
        }
    }

    return swaps / 2;
}

int main() {
    char *str1 = NULL;
    char *str2 = NULL;
    size_t len1, len2;
    size_t size1 = MAX_STRING_LEN;
    size_t size2 = MAX_STRING_LEN;

    str1 = (char *)malloc(size1 * sizeof(char));
    if (str1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    str2 = (char *)malloc(size2 * sizeof(char));
    if (str2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(str1);
        return 1;
    }

    printf("Enter first binary string: ");
    if (fgets(str1, size1, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(str1);
        free(str2);
        return 1;
    }
    
    len1 = strcspn(str1, "\n");
    str1[len1] = '\0';

    printf("Enter second binary string: ");
    if (fgets(str2, size2, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(str1);
        free(str2);
        return 1;
    }
    
    len2 = strcspn(str2, "\n");
    str2[len2] = '\0';

    int result = minSwaps(str1, len1, str2, len2);

    if (result == -1) {
        printf("Conversion not possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    free(str1);
    free(str2);

    return 0;
}