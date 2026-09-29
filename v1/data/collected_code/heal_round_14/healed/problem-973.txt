#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void leftRotateString(char* str, int n) {
    if (str == NULL || n <= 0) {
        return;
    }

    size_t len = strlen(str);
    if (len <= 1 || n > len) {
        return;
    }

    int rotations = n % len;
    char* buffer = (char*)calloc(len + 1, sizeof(char));
    if (buffer == NULL) {
        return;
    }

    if (rotations <= len) {
        memcpy(buffer, str + rotations, len - rotations);
        memcpy(buffer + len - rotations, str, rotations);
    } else {
        free(buffer);
        return;
    }

    if (len < len + 1) {
        strncpy(str, buffer, len);
        str[len] = '\0';
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
