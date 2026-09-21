#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leftRotateString(char *str, size_t rotations) {
    size_t len = 0;
    char *temp;

    if (str == NULL) {
        return;
    }

    while (str[len] != '\0') {
        len++;
    }

    if (len == 0 || rotations == 0 || rotations % len == 0) {
        return;
    }

    rotations = rotations % len;

    temp = (char *)malloc(rotations);
    if (temp == NULL) {
        return;
    }

    memcpy(temp, str, rotations);
    memmove(str, str + rotations, len - rotations);
    memcpy(str + len - rotations, temp, rotations);

    free(temp);
}

int main(void) {
    char str[] = "Hello, World!";
    size_t rotations = 7;

    leftRotateString(str, rotations);

    printf("%s\n", str);

    return 0;
}