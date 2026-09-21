#include <stdio.h>
#include <string.h>

int findRotations(const char *str, size_t len) {
    char temp[2*len + 1];
    if (snprintf(temp, sizeof(temp), "%.*s%.*s", (int)len, str, (int)len, str) >= (int)(sizeof(temp))) {
        return -1;
    }
    for (size_t i = 0; i < len; i++) {
        if (strncmp(temp + i, str, len) == 0) {
            return i;
        }
    }
    return len;
}

int main() {
    const char input[] = "abcde";
    size_t input_len = sizeof(input) - 1;
    int rotations = findRotations(input, input_len);
    if (rotations != -1) {
        printf("Minimum number of rotations: %d\n", rotations);
    } else {
        printf("Error in finding rotations.\n");
    }
    return 0;
}