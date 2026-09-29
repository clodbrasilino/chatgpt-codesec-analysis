#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void leftRotateString(char* str, int n) {
    if (str == NULL || str[0] == '\0' || n <= 0) {
        return;
    }

    size_t len = strlen(str);
    if (len <= 1) {
        return;
    }

    int rotations = n % len;
    char* buffer = (char*)calloc(len + 1, sizeof(char));
    if (buffer == NULL) {
        return;
    }

    if (rotations <= len) {
        memcpy(buffer, str + rotations, len - rotations);
    }

    if (rotations <= len) {
        memcpy(buffer + len - rotations, str, rotations);
    }

    buffer[len] = '\0';

    if (len <= strlen(str)) {
        memcpy(str, buffer, len + 1);
    }

    free(buffer);
}

int main() {
    char str[] = "Hello, World!";
    int rotations = 4;

    leftRotateString(str, rotations);

    printf("%s\n", str);

    return 0;
}