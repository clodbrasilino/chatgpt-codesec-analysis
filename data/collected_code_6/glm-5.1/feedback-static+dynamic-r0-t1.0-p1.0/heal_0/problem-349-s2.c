#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_binary_string(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return false;
    }

    for (size_t i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
    }

    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    if (is_binary_string(argv[1])) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}