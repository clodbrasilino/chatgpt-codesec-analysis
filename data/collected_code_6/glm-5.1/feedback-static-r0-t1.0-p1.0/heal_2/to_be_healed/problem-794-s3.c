#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
  */

bool matches_pattern(const char *str) {
    if (str == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     *  'SIZE_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'SIZE_MAX'
     */
    size_t len = strnlen(str, SIZE_MAX);

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