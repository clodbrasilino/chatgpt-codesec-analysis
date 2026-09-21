#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minSwaps(const char *str1, const char *str2, size_t len1, size_t len2) {
    if (len1 != len2) {
        return -1;
    }

    int count1 = 0, count2 = 0;
    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != '0' && str1[i] != '1') return -1;
        if (str2[i] != '0' && str2[i] != '1') return -1;
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
        return 1;
    }
    len1 = strcspn(str1, "\n");
    str1[len1] = '\0';

    printf("Enter second binary string: ");
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        return 1;
    }
    len2 = strcspn(str2, "\n");
    str2[len2] = '\0';

    int result = minSwaps(str1, str2, len1, len2);

    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}