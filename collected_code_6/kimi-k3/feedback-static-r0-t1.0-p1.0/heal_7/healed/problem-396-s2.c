#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int starts_ends_same_char(const char *str, size_t max_len) {
    size_t len = 0;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; i < max_len; i++) {
        if (str[i] == '\0') {
            break;
        }
        len++;
    }

    if (len == 0) {
        return 0;
    }

    return str[0] == str[len - 1];
}

int main(void) {
    char *input = NULL;
    size_t size = 0;
    ssize_t len;

    len = getline(&input, &size, stdin);
    if (len == -1) {
        free(input);
        return 1;
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (starts_ends_same_char(input, (size_t)len)) {
        printf("String starts and ends with the same character.\n");
    } else {
        printf("String does not start and end with the same character.\n");
    }

    free(input);
    return 0;
}