#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void leftRotateString(char* str, int n) {
    if (str == NULL || n <= 0) {
        return;
    }
    
    size_t len = strlen(str);
    if (len <= 1) {
        return;
    }

    int rotations = n % len;
    char* buffer = malloc(len + 1);

    if (buffer == NULL) {
        return;
    }

    strncpy(buffer, str + rotations, len - rotations);
    strncpy(buffer + len - rotations, str, rotations);
    buffer[len] = '\0'; // Important! This ensures that buffer is null-terminated
    strncpy(str, buffer, len);
    str[len] = '\0'; // Important! This ensures that str is null-terminated

    free(buffer);
}

int main() {
    char str[] = "Hello, World!";
    int rotations = 4;

    leftRotateString(str, rotations);

    printf("%s\n", str);

    return 0;
}