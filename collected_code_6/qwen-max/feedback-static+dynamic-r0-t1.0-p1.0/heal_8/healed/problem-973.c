#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate(char *str, int d) {
    if (str == NULL) return;

    size_t n = strlen(str);
    if (n == 0) return;

    d = (d % n + n) % n;
    if (d <= 0) return;

    char *temp = malloc(d + 1);
    if (temp == NULL) return;

    memcpy(temp, str, d);
    temp[d] = '\0';
    memmove(str, str + d, n - d + 1);
    strncat(str, temp, d);

    free(temp);
}

int main() {
    char str[] = "abcdef";
    int d = 2;
    left_rotate(str, d);
    printf("%s\n", str);
    return 0;
}