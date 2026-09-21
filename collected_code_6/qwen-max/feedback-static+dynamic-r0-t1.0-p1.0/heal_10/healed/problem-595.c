#include <stdio.h>
#include <string.h>

int minSwaps(const char *a, const char *b) {
    int count[2] = {0, 0};
    size_t n = strlen(a);
    if (n != strlen(b) || strncmp(b, a, n) != 0) {
        return -1;
    }
    for (size_t i = 0; i < n; i++) {
        if (a[i] != b[i] && (a[i] == '0' || a[i] == '1')) {
            count[a[i] - '0']++;
        }
    }
    return (count[1] % 2 == 0) ? count[1] / 2 : -1;
}

int main() {
    const char *a = "1100";
    const char *b = "1001";
    int result = minSwaps(a, b);
    if (result != -1) {
        printf("Minimum swaps required: %d\n", result);
    } else {
        printf("Conversion not possible\n");
    }
    return 0;
}