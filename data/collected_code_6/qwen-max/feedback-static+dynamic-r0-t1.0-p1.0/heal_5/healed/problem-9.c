#include <stdio.h>
#include <string.h>

int findMinRotations(const char *str, size_t len) {
    char temp[2 * len + 1];
    if (len > 0 && len < sizeof(temp)/2) {
        snprintf(temp, sizeof(temp), "%s%s", str, str);
        for (size_t i = 1; i <= len; i++) {
            if (strncmp(temp + i, str, len) == 0) {
                return i;
            }
        }
    }
    return len;
}

int main() {
    const char str[] = "abcde";
    size_t len = strlen(str);
    if (len > 0) {
        printf("Minimum rotations: %zu\n", (size_t)findMinRotations(str, len));
    } else {
        printf("Invalid input string.\n");
    }
    return 0;
}