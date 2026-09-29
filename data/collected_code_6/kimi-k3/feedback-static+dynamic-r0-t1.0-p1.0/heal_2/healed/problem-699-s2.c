#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int min_swaps(const char *str1, size_t len1, const char *str2, size_t len2) {
    if (len1 != len2) {
        return -1;
    }

    int count0_str1 = 0, count1_str1 = 0;
    int count0_str2 = 0, count1_str2 = 0;

    for (size_t i = 0; i < len1; i++) {
        if (str1[i] == '0') count0_str1++;
        else if (str1[i] == '1') count1_str1++;
        else return -1;

        if (str2[i] == '0') count0_str2++;
        else if (str2[i] == '1') count1_str2++;
        else return -1;
    }

    if (count0_str1 != count0_str2 || count1_str1 != count1_str2) {
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

int main(void) {
    char *str1 = NULL;
    char *str2 = NULL;
    size_t size1 = 0;
    size_t size2 = 0;
    ssize_t len1, len2;

    printf("Enter the first binary string: ");
    len1 = getline(&str1, &size1, stdin);
    if (len1 == -1) {
        fprintf(stderr, "Error reading input\n");
        free(str1);
        return 1;
    }
    if (len1 > 0 && str1[len1 - 1] == '\n') {
        str1[len1 - 1] = '\0';
        len1--;
    }

    printf("Enter the second binary string: ");
    len2 = getline(&str2, &size2, stdin);
    if (len2 == -1) {
        fprintf(stderr, "Error reading input\n");
        free(str1);
        free(str2);
        return 1;
    }
    if (len2 > 0 && str2[len2 - 1] == '\n') {
        str2[len2 - 1] = '\0';
        len2--;
    }

    int result = min_swaps(str1, (size_t)len1, str2, (size_t)len2);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("Minimum number of swaps required: %d\n", result);
    }

    free(str1);
    free(str2);

    return 0;
}