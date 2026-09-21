#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate(char *str, size_t len, int d) {
    d = (d % (int)len + len) % len;
    if (d == 0) return;

    char *temp = (char *)malloc(d + 1);
    if (temp == NULL) return;

    memcpy(temp, str, d);
    memmove(str, str + d, len - d + 1);
    temp[d] = '\0';
    strncat(str, temp, d + 1);

    free(temp);
}

int main() {
    char str[] = "abcdef";
    int d = 2;
    left_rotate(str, strlen(str), d);
    printf("%s\n", str);
    return 0;
}