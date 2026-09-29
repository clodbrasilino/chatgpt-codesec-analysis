#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate_string(char *str, int n) {
    if (str == NULL || n <= 0) {
        return;
    }

    int len = strlen(str);
    if (len == 0) {
        return;
    }

    n = n % len;
    if (n == 0) {
        return;
    }

    char *temp = malloc(n + 1);
    if (temp == NULL) {
        return;
    }

    memcpy(temp, str, n);
    temp[n] = '\0';
    memmove(str, str + n, len - n + 1);
    memcpy(str + len - n, temp, n);
    str[len] = '\0';

    free(temp);
}

int main(void) {
    char buffer[100];

    strncpy(buffer, "abcdef", sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    left_rotate_string(buffer, 2);
    printf("%s\n", buffer);

    strncpy(buffer, "hello", sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    left_rotate_string(buffer, 7);
    printf("%s\n", buffer);

    strncpy(buffer, "test", sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    left_rotate_string(buffer, 0);
    printf("%s\n", buffer);

    strncpy(buffer, "", sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    left_rotate_string(buffer, 3);
    printf("%s\n", buffer);

    return 0;
}