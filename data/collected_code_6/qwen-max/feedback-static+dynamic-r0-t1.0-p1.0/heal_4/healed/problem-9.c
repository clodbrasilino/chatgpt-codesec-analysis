#include <stdio.h>
#include <string.h>

int findMinRotations(const char *str, size_t len) {
    char temp[2 * len + 1];
    snprintf(temp, sizeof(temp), "%s%s", str, str);

    for (size_t i = 1; i <= len; i++) {
        if (strncmp(temp + i, str, len) == 0) {
            return i;
        }
    }
    return len;
}

int main() {
    const char str[] = "abcde";
    size_t len = strlen(str);
    printf("Minimum rotations: %zu\n", (size_t)findMinRotations(str, len));
    return 0;
}