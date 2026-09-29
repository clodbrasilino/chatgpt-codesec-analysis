#include <stdio.h>
#include <string.h>

int max_diff_sub(const char *str, size_t len) {
    int max_diff = 0, count = 0;

    for (size_t i = 0; i < len; i++) {
        count += (str[i] == '0') ? 1 : -1;
        if (count < 0) count = 0;
        if (count > max_diff) max_diff = count;
    }

    count = 0;
    for (size_t i = len - 1; i >= 0; i--) {
        count += (str[i] == '1') ? 1 : -1;
        if (count < 0) count = 0;
        if (count > max_diff) max_diff = count;
    }

    return max_diff;
}

int main() {
    const char str[] = "100010001";
    size_t len = sizeof(str) - 1;
    int result = max_diff_sub(str, len);
    printf("Maximum difference: %d\n", result);
    return 0;
}