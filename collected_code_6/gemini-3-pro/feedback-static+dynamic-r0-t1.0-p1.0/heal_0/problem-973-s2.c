#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void leftRotateString(char *str, size_t d) {
    if (str == NULL) {
        return;
    }

    size_t len = strlen(str);
    if (len == 0 || d == 0) {
        return;
    }

    d = d % len;
    if (d == 0) {
        return;
    }

    char *temp = (char *)malloc((d + 1) * sizeof(char));
    if (temp == NULL) {
        return;
    }

    strncpy(temp, str, d);
    temp[d] = '\0';

    memmove(str, str + d, len - d);
    strncpy(str + len - d, temp, d);

    free(temp);
}

int main() {
    char str[] = "HelloWorld";
    size_t d = 3;

    leftRotateString(str, d);
    printf("%s\n", str);

    return 0;
}