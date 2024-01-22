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
    char* buffer = (char*)malloc(len + 1);

    if (buffer == NULL) {
        return;
    }

    memmove(buffer, str + rotations, len - rotations);
    memmove(buffer + len - rotations, str, rotations);
    buffer[len] = '\0';

    memmove(str, buffer, len);
    str[len] = '\0';

    free(buffer);
}

int main() {
    char str[] = "Hello, World!";
    int rotations = 4;

    leftRotateString(str, rotations);

    printf("%s\n", str);

    return 0;
}