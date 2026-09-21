#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

bool is_concatenation(const char *str, const char *sub, size_t str_len, size_t sub_len) {
    if (str == NULL || sub == NULL) {
        return false;
    }

    if (sub_len == 0) {
        return false;
    }

    if (str_len % sub_len != 0) {
        return false;
    }

    if (str_len == 0) {
        return true;
    }

    size_t repetitions = str_len / sub_len;

    for (size_t i = 0; i < repetitions; i++) {
        if (memcmp(str + i * sub_len, sub, sub_len) != 0) {
            return false;
        }
    }

    return true;
}

int main(int argc, char const * const * argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <substring>\n", argv[0]);
        return 1;
    }

    size_t str_len = strnlen(argv[1], SIZE_MAX);
    size_t sub_len = strnlen(argv[2], SIZE_MAX);

    if (is_concatenation(argv[1], argv[2], str_len, sub_len)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}