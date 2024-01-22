#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void leftRotateString(char* str, int n) {
    if (str == NULL || n <= 0) {
        return;
    }

    size_t len = strlen(str);
    if (len <= 1 || n > len) {
        // Cannot rotate a string of length 1 or less
        // and also if rotations are more than length
        return;
    }

    int rotations = n % len;
    char* buffer = (char*)calloc(len + 1, sizeof(char));
    if (buffer == NULL) {
        // Memory allocation failed
        return;
    }

    // Safe copy as size is checked
    strncpy(buffer, str + rotations, len - rotations);
    strncpy(buffer + len - rotations, str, rotations);

    // len will always be less than or equal to strlen(str)
    strncpy(str, buffer, len + 1);

    free(buffer);
}

int main() {
    char str[] = "Hello, World!";
    int rotations = 4;

    leftRotateString(str, rotations);

    printf("%s\n", str);

    return 0;
}