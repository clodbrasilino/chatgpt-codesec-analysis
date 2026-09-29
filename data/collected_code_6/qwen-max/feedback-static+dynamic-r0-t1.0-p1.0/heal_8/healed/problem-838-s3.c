#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minSwapsToEqual(const char *a, const char *b, size_t len) {
    int mismatch[2] = {0};
    for (size_t i = 0; i < len; i++) {
        if (a[i] != b[i] && (a[i] == '0' || a[i] == '1')) {
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
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);

    if (len_a > 0 && len_a == len_b) {
        int result = minSwapsToEqual(a, b, len_a);
        printf("%d\n", result);
    } else {
        printf("-1\n");
    }
    return 0;
}