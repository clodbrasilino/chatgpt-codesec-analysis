#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int match_ab23(const char *str, size_t len) {
    if (len < 3) return 0;
    if (str[0] != 'a') return 0;
    if (str[1] != 'b') return 0;
    if (str[2] != 'b') return 0;
    if (len == 3) return 1;
    if (len == 4 && str[3] == 'b') return 1;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t len = strlen(argv[1]);
    int matched = match_ab23(argv[1], len);
    printf("%s\n", matched ? "match" : "no match");
    return EXIT_SUCCESS;
}