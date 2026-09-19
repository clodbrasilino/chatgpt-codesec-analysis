#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minSwapsToEqual(const char *a, const char *b, int len) {
    int mismatch[2] = {0};
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            mismatch[a[i] - '0']++;
        }
    }
    if (mismatch[0] != mismatch[1]) {
        return -1;
    }
    return (mismatch[0] + 1) / 2;
}

int main() {
    const char *a = "1100";
    const char *b = "1001";
    int len = strlen(a);
    int result = minSwapsToEqual(a, b, len);
    printf("%d\n", result);
    return 0;
}