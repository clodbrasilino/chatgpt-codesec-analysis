#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int starts_ends_same(const char *str, size_t max_len) {
    if (str == NULL || *str == '\0') {
        return 0;
    }

    size_t len = strnlen(str, max_len);
    if (len == 0) {
        return 0;
    }

    return str[0] == str[len - 1];
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }

    if (starts_ends_same(argv[1], 4096)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}