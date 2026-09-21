#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int countSwaps(const char *a, const char *b, size_t len) {
    int mismatch = 0;
    for (size_t i = 0; i < len; ++i) {
        if (a[i] != b[i]) {
            mismatch++;
        }
    }
    return mismatch / 2 + (mismatch % 2);
}

int main() {
    const char *str1 = "1100";
    const char *str2 = "1001";
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (len1 != len2) {
        printf("Error: The two strings must be of the same length.\n");
        return 1;
    }

    int swaps = countSwaps(str1, str2, len1);
    printf("Minimum number of swaps required: %d\n", swaps);
    return 0;
}