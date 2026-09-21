#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate_string(char *str, size_t size, int n) {
    if (str == NULL || size == 0 || n <= 0) {
        return;
    }

    size_t len = strnlen(str, size);
    if (len == 0 || len >= size) {
        return;
    }

    n = (int)((size_t)n % len);
    if (n == 0) {
        return;
    }

    if ((size_t)n > len || (size_t)n >= size) {
        return;
    }

    char *temp = malloc((size_t)n + 1);
    if (temp == NULL) {
        return;
    }

    memcpy(temp, str, (size_t)n);
    temp[n] = '\0';

    size_t remaining = len - (size_t)n;
    if (remaining + 1 > size) {
        free(temp);
        return;
    }

    memmove(str, str + n, remaining + 1);

    if ((size_t)n > size - remaining) {
        free(temp);
        return;
    }

    memcpy(str + remaining, temp, (size_t)n);
    free(temp);
}

int main(void) {
    char buffer[100] = {0};

    snprintf(buffer, sizeof(buffer), "abcdef");
    left_rotate_string(buffer, sizeof(buffer), 2);
    printf("%s\n", buffer);

    snprintf(buffer, sizeof(buffer), "hello");
    left_rotate_string(buffer, sizeof(buffer), 7);
    printf("%s\n", buffer);

    snprintf(buffer, sizeof(buffer), "test");
    left_rotate_string(buffer, sizeof(buffer), 0);
    printf("%s\n", buffer);

    buffer[0] = '\0';
    left_rotate_string(buffer, sizeof(buffer), 3);
    printf("%s\n", buffer);

    return 0;
}