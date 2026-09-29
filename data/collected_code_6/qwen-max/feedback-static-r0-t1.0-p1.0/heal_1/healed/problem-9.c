#include <stdio.h>
#include <string.h>

int findMinRotations(const char *str) {
    size_t n = strlen(str);
    char temp[2*n + 1];
    snprintf(temp, sizeof(temp), "%s%s", str, str);

    for (size_t i = 1; i <= n; i++) {
        if (strncmp(temp + i, str, n) == 0) {
            return (int)i;
        }
    }
    return (int)n;
}

int main() {
    const char str[] = "abcde";
    printf("Minimum rotations: %d\n", findMinRotations(str));
    return 0;
}