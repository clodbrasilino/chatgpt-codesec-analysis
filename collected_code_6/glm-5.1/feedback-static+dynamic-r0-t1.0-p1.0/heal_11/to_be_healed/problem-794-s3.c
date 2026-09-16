#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool matches_pattern(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = strlen(str);

    if (len < 2) {
        return false;
    }

    if (str[0] != 'a') {
        return false;
    }

    if (str[len - 1] != 'b') {
        return false;
    }

    for (size_t i = 1; i < len - 1; i++) {
        if (str[i] == '\0') {
            return false;
        }
    }

    return true;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    if (matches_pattern(argv[1])) {
        printf("Match\n");
    } else {
        printf("No Match\n");
    }

    return 0;
}