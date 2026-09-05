#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool match_a_followed_by_zero_or_one_b(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = strlen(str);
    if (len < 1) {
        return false;
    }

    if (str[0] != 'a') {
        return false;
    }

    if (len == 1) {
        return true;
    }

    if (len == 2 && str[1] == 'b') {
        return true;
    }

    return false;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    bool result = match_a_followed_by_zero_or_one_b(argv[1]);
    printf("%d\n", result);

    return 0;
}