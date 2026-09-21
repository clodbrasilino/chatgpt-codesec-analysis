#include <stdio.h>
#include <string.h>

int findRotations(const char *str, size_t len) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[2*len + 1];
    snprintf(temp, sizeof(temp), "%s%s", str, str);
    for (size_t i = 1; i < len; i++) {
        if (strncmp(temp + i, str, len) == 0) {
            return (int)i;
        }
    }
    return (int)len;
}

int main() {
    const char input[] = "abcde";
    size_t len = sizeof(input) - 1;
    int rotations = findRotations(input, len);
    printf("Minimum number of rotations: %d\n", rotations);
    return 0;
}