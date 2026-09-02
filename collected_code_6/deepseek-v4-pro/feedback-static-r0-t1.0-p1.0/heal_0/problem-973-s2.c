#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate_string(char *str, int n) {
    int len = strlen(str);
    if (len == 0 || n <= 0) {
        return;
    }
    n = n % len;
    if (n == 0) {
        return;
    }

    char *temp = malloc(n);
    if (temp == NULL) {
        return;
    }

    memcpy(temp, str, n);
    memmove(str, str + n, len - n + 1);
    memcpy(str + len - n, temp, n);

    free(temp);
}

int main(void) {
    char buffer[100];

    strcpy(buffer, "abcdef");
    left_rotate_string(buffer, 2);
    printf("%s\n", buffer);

    strcpy(buffer, "hello");
    left_rotate_string(buffer, 7);
    printf("%s\n", buffer);

    strcpy(buffer, "test");
    left_rotate_string(buffer, 0);
    printf("%s\n", buffer);

    strcpy(buffer, "");
    left_rotate_string(buffer, 3);
    printf("%s\n", buffer);

    return 0;
}