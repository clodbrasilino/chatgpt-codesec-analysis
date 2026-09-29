#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
        for (size_t j = 0; j < sub_len; j++) {
            if (str[i * sub_len + j] != sub[j]) {
                return false;
            }
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

    if (is_concatenation(argv[1], argv[2])) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}