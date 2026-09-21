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

    if ((size_t)n >= size) {
        return;
    }

    char *temp = malloc((size_t)n + 1);
    if (temp == NULL) {
        return;
    }

    if ((size_t)n < size) {
        memcpy(temp, str, (size_t)n);
    } else {
        free(temp);
        return;
    }
    temp[n] = '\0';

    if ((size_t)n < len) {
        memmove(str, str + n, len - (size_t)n + 1);
    } else {
        free(temp);
        return;
    }

    if (len - (size_t)n + (size_t)n < size) {
        if (len - (size_t)n + (size_t)n < size && (size_t)n <= size - (len - (size_t)n)) {
            memcpy(str + len - (size_t)n, temp, (size_t)n);
        }
    }
    
    if (len < size) {
        str[len] = '\0';
    }

    free(temp);
}

int main(void) {
    char buffer[100] = {0};

    snprintf(buffer, sizeof(buffer), "%.*s", (int)(sizeof(buffer) - 1), "abcdef");
    left_rotate_string(buffer, sizeof(buffer), 2);
    printf("%s\n", buffer);

    snprintf(buffer, sizeof(buffer), "%.*s", (int)(sizeof(buffer) - 1), "hello");
    left_rotate_string(buffer, sizeof(buffer), 7);
    printf("%s\n", buffer);

    snprintf(buffer, sizeof(buffer), "%.*s", (int)(sizeof(buffer) - 1), "test");
    left_rotate_string(buffer, sizeof(buffer), 0);
    printf("%s\n", buffer);

    buffer[0] = '\0';
    left_rotate_string(buffer, sizeof(buffer), 3);
    printf("%s\n", buffer);

    return 0;
}