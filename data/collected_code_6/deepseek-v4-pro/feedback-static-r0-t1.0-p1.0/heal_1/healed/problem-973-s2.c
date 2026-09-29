#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate_string(char *str, int n) {
    if (str == NULL || str[0] == '\0' || n <= 0) {
        return;
    }

    size_t len = strlen(str);
    n = (int)((size_t)n % len);
    if (n == 0) {
        return;
    }

    char *temp = malloc((size_t)n);
    if (temp == NULL) {
        return;
    }

    memcpy(temp, str, (size_t)n);
    memmove(str, str + n, len - (size_t)n + 1);
    memcpy(str + len - (size_t)n, temp, (size_t)n);

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