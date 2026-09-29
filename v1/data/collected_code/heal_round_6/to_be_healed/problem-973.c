#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void leftRotateString(char* str, int n) {
    if (str == NULL || n <= 0) {
        return;
    }

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t len = strlen(str);
    if (len <= 1) {
        return;
    }

    int rotations = n % len;
    char* buffer = malloc(len);

    if (buffer == NULL) {
        return;
    }

    memmove(buffer, str + rotations, len - rotations);
    memmove(buffer + len - rotations, str, rotations);
    memmove(str, buffer, len);
  
    free(buffer);
}

int main() {
    char str[] = "Hello, World!";
    int rotations = 4;

    leftRotateString(str, rotations);

    printf("%s\n", str);

    return 0;
}