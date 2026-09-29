#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STR_LEN 4096

bool all_chars_same(const char *str, size_t max_len)
{
    size_t i;
    size_t len;

    if (str == NULL) {
        return false;
    }

    len = strnlen(str, max_len);
    if (len == 0) {
        return false;
    }

    for (i = 1; i < len; i++) {
        if (str[i] != str[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read_len;

    read_len = getline(&buffer, &buffer_size, stdin);
    if (read_len < 0 || buffer == NULL) {
        free(buffer);
        printf("False\n");
        fflush(stdout);
        return 0;
    }

    buffer[strcspn(buffer, "\r\n")] = '\0';

    if (all_chars_same(buffer, (size_t)read_len)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    free(buffer);
    fflush(stdout);
    return 0;
}