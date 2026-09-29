#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_binary_string(const char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return false;
    }

    for (size_t i = 0; i < max_len; i++) {
        if (str[i] == '\0') {
            return i > 0;
        }
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
    }

    return false;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    if (is_binary_string(argv[1], sizeof(argv[1]))) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}