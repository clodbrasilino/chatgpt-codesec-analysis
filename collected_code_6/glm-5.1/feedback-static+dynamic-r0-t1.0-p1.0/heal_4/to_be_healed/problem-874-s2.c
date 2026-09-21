#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <substring>\n", argv[0]);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(argv[1]);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t sub_len = strlen(argv[2]);

    if (is_concatenation(argv[1], argv[2], str_len, sub_len)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}