#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int starts_with_substring(const char *str, const size_t str_len, const char *sub, const size_t sub_len) {
    if (str == NULL || sub == NULL) {
        return 0;
    }

    if (sub_len == 0) {
        return 1;
    }

    if (str_len < sub_len) {
        return 0;
    }

    return strncmp(str, sub, sub_len) == 0;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <substring>\n", argv[0]);
        return 1;
    }

    size_t str_len = strnlen(argv[1], SIZE_MAX);
    size_t sub_len = strnlen(argv[2], SIZE_MAX);

    if (starts_with_substring(argv[1], str_len, argv[2], sub_len)) {
        printf("Match\n");
    } else {
        printf("No match\n");
    }

    return 0;
}