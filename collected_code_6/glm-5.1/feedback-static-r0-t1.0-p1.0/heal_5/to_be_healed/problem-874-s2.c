#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_concatenation(const char *str, const char *sub) {
    if (str == NULL || sub == NULL) {
        return false;
    }

    size_t str_len = strlen(str);
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
        if (strncmp(str + (i * sub_len), sub, sub_len) != 0) {
            return false;
        }
    }

    return true;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
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