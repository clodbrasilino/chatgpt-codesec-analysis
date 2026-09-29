#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate_string(char *str, int n) {
    if (str == NULL || str[0] == '\0' || n <= 0) {
        return;
    }

    size_t len = strnlen(str, 100);
    if (len == 0 || len >= 100) {
        return;
    }

    n = (int)((size_t)n % len);
    if (n == 0) {
        return;
    }

    char *temp = malloc((size_t)n + 1);
    if (temp == NULL) {
        return;
    }

    memcpy(temp, str, (size_t)n);
    temp[n] = '\0';

    memmove(str, str + n, len - (size_t)n);
    str[len - (size_t)n] = '\0';

    memcpy(str + len - (size_t)n, temp, (size_t)n);
    str[len] = '\0';

    free(temp);
}

int main(void) {
    char buffer[100] = {0};

    snprintf(buffer, sizeof(buffer), "%.*s", (int)(sizeof(buffer) - 1), "abcdef");
    left_rotate_string(buffer, 2);
    printf("%s\n", buffer);

    snprintf(buffer, sizeof(buffer), "%.*s", (int)(sizeof(buffer) - 1), "hello");
    left_rotate_string(buffer, 7);
    printf("%s\n", buffer);

    snprintf(buffer, sizeof(buffer), "%.*s", (int)(sizeof(buffer) - 1), "test");
    left_rotate_string(buffer, 0);
    printf("%s\n", buffer);

    buffer[0] = '\0';
    left_rotate_string(buffer, 3);
    printf("%s\n", buffer);

    return 0;
}