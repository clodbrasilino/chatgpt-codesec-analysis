#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_concatenation(const char *str, const char *sub) {
    if (str == NULL || sub == NULL) {
        return false;
    }

    size_t str_len = 0;
    while (str[str_len] != '\0') {
        str_len++;
    }

    size_t sub_len = 0;
    while (sub[sub_len] != '\0') {
        sub_len++;
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
        size_t j = 0;
        while (j < sub_len) {
            if (str[i * sub_len + j] != sub[j]) {
                return false;
            }
            j++;
        }
    }

    return true;
}

int main(int argc, char const * const * argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <substring>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (is_concatenation(argv[1], argv[2])) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return EXIT_SUCCESS;
}