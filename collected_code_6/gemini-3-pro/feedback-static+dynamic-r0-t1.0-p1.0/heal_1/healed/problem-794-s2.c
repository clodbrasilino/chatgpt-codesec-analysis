#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 4096

int match_pattern(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strnlen(str, MAX_STR_LEN);
    if (len < 2 || len == MAX_STR_LEN) {
        return 0;
    }

    const void *a_ptr = memchr(str, 'a', len);
    if (a_ptr == NULL) {
        return 0;
    }

    if (str[len - 1] != 'b') {
        return 0;
    }

    if ((const char *)a_ptr >= (str + len - 1)) {
        return 0;
    }

    return 1;
}

int main(void) {
    const char *test_strings[] = {
        "axxxb",
        "baxb",
        "ab",
        "a",
        "b",
        "axxxbx",
        "zb",
        NULL
    };

    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++) {
        int result = match_pattern(test_strings[i]);
        if (test_strings[i] != NULL) {
            printf("\"%s\": %d\n", test_strings[i], result);
        } else {
            printf("NULL: %d\n", result);
        }
    }

    return 0;
}