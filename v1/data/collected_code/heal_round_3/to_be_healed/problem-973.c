#include <stdio.h>
#include <string.h>

void leftRotateString(char* str, int n) {
    if (!str) {
        return;
    }

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len = strlen(str);
    if (len <= 0) {
        return;
    }

    int rotations = n % len;

    for (int i = 0; i < rotations; i++) {
        char firstChar = str[0];

        memmove(str, str + 1, len - 1);

        str[len - 1] = firstChar;
    }
}

int main() {
    char str[] = "Hello, World!";
    int rotations = 4;

    leftRotateString(str, rotations);

    printf("%s\n", str);

    return 0;
}