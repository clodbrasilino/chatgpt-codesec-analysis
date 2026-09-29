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

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    size_t len = strnlen(argv[1], 1024);
    if (is_binary_string(argv[1], len)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}