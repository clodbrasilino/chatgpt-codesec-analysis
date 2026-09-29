#include <stdio.h>
#include <string.h>

int min_swaps(const char *s1, const char *s2) {
    int len = strlen(s1);
    int count1 = 0, count2 = 0;
    int mismatched_ones = 0, mismatched_zeros = 0;
    int swaps = 0;

    for (int i = 0; i < len; i++) {
        if (s1[i] == '1') count1++;
        if (s2[i] == '1') count2++;
    }

    if (count1 != count2) return -1;

    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') mismatched_ones++;
            else mismatched_zeros++;
        }
    }

    swaps = (mismatched_ones > mismatched_zeros) ? mismatched_ones : mismatched_zeros;
    return swaps;
}

int main(void) {
    char str1[101] = {0};
    char str2[101] = {0};

    printf("Enter first binary string: ");
    if (scanf("%100s", str1) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    printf("Enter second binary string: ");
    if (scanf("%100s", str2) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    if (len1 != len2) {
        printf("Strings must be of equal length\n");
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