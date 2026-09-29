#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

bool is_alternating(const char *str, size_t max_len) {
    size_t len = strnlen(str, max_len);
    if (len < 2) {
        return false;
    }

    char a = str[0];
    char b = str[1];

    if (a == b) {
        return false;
    }

    for (size_t i = 2; i < len; i++) {
        if (i % 2 == 0) {
            if (str[i] != a) {
                return false;
            }
        } else {
            if (str[i] != b) {
                return false;
            }
        }
    }

    return true;
}

int main(void) {
    char *str = NULL;
    size_t len = 0;
    ssize_t read;

    if ((read = getline(&str, &len, stdin)) != -1) {
        if (read > 0 && str[read - 1] == '\n') {
            str[read - 1] = '\0';
        }
        if (is_alternating(str, len)) {
            printf("true\n");
        } else {
            printf("false\n");
        }
        free(str);
    }
    return 0;
}