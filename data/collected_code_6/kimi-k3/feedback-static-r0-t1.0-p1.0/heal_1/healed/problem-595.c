#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    char str1[100], str2[100];
    size_t len1, len2;

    printf("Enter first binary string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    len1 = strlen(str1);
    if (len1 > 0 && str1[len1 - 1] == '\n') {
        str1[len1 - 1] = '\0';
        len1--;
    }

    printf("Enter second binary string: ");
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    len2 = strlen(str2);
    if (len2 > 0 && str2[len2 - 1] == '\n') {
        str2[len2 - 1] = '\0';
        len2--;
    }

    int result = minSwaps(str1, len1, str2, len2);

    if (result == -1) {
        printf("Conversion not possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    return 0;
}