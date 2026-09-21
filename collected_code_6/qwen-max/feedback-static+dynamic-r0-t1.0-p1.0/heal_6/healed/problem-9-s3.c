#include <stdio.h>
#include <string.h>

int findRotations(const char *str, size_t len) {
    char temp[2*len + 1];
    snprintf(temp, sizeof(temp), "%s%s", str, str);
    for (size_t i = 1; i <= len; i++) {
        if (strncmp(temp + i, str, len) == 0) {
            return (int)i;
        }
    }
    return (int)len;
}

int main() {
    const char input[] = "abcde";
    size_t len = strlen(input);
    int rotations = findRotations(input, len);
    printf("Minimum number of rotations: %d\n", rotations);
    return 0;
}