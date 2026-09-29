#include <stdio.h>
#include <string.h>

int countSwaps(const char *str1, const char *str2, int len) {
    int mismatchCount = 0;
    for (int i = 0; i < len; i++) {
        if (str1[i] != str2[i]) {
            mismatchCount++;
        }
    }
    return mismatchCount / 2;
}

int main() {
    char str1[256], str2[256];
    printf("Enter the first binary string: ");
    if (fgets(str1, sizeof(str1), stdin) != NULL) {
        str1[strcspn(str1, "\n")] = 0;
    } else {
        return 1;
    }
    printf("Enter the second binary string: ");
    if (fgets(str2, sizeof(str2), stdin) != NULL) {
        str2[strcspn(str2, "\n")] = 0;
    } else {
        return 1;
    }

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len1 != len2) {
        printf("Strings must be of the same length\n");
        return 1;
    }

    int swaps = countSwaps(str1, str2, len1);
    printf("Minimum number of swaps required: %d\n", swaps);

    return 0;
}