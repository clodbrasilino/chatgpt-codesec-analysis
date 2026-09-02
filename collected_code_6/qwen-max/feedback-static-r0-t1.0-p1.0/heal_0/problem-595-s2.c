#include <stdio.h>
#include <string.h>

int countSwaps(const char *a, const char *b, int len) {
    int mismatch = 0, count[2] = {0, 0};
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            mismatch++;
            count[a[i] - '0']++;
        }
    }

    return mismatch / 2 + (mismatch & 1 ? 1 : 0);
}

int main() {
    char str1[] = "1100";
    char str2[] = "1001";
    int len = strlen(str1);

    if (len != strlen(str2)) {
        printf("Error: The two strings must be of the same length.\n");
        return 1;
    }

    int swaps = countSwaps(str1, str2, len);
    printf("Minimum number of swaps required: %d\n", swaps);
    return 0;
}