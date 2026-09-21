#include <stdio.h>
#include <string.h>

int findRotations(const char *str) {
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
    const char input[] = "abcde";
    int rotations = findRotations(input);
    printf("Minimum number of rotations: %d\n", rotations);
    return 0;
}