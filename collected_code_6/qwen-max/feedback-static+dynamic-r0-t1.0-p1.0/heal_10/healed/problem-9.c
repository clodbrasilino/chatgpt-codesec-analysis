#include <stdio.h>
#include <string.h>

int findMinRotations(const char *str, size_t len) {
    if (len == 0) return 0;
    char temp[len * 2 + 1];
    snprintf(temp, sizeof(temp), "%s%s", str, str);
    for (size_t i = 1; i < len; i++) {
        if (strncmp(temp + i, str, len) == 0) {
            return (int)i;
        }
    }
    return (int)len;
}

int main() {
    const char str[] = "abcde";
    size_t len = strlen(str);
    if (len > 0 && len < sizeof(str) / 2 - 1) {
        printf("Minimum rotations: %zu\n", (size_t)findMinRotations(str, len));
    } else {
        printf("Invalid input string.\n");
    }
    return 0;
}