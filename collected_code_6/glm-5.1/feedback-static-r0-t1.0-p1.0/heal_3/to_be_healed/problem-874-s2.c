#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_concatenation(const char *str, const char *sub) {
    if (str == NULL || sub == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t sub_len = strlen(sub);

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
        return EXIT_FAILURE;
    }

    if (is_concatenation(argv[1], argv[2])) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return EXIT_SUCCESS;
}