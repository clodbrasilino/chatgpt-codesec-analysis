#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int starts_with_substring(const char *str, const char *sub) {
    if (str == NULL || sub == NULL) {
        return 0;
    }

    size_t sub_len = strlen(sub);
    if (sub_len == 0) {
        return 1;
    }

    size_t str_len = strlen(str);
    if (sub_len > str_len) {
        return 0;
    }

    return strncmp(str, sub, sub_len) == 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <substring>\n", argv[0]);
        return 1;
    }

    if (starts_with_substring(argv[1], argv[2])) {
        printf("Match\n");
    } else {
        printf("No match\n");
    }

    return 0;
}