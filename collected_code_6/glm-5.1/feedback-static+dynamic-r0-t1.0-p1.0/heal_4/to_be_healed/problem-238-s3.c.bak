#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count_substrings(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strlen(str);
    return len * (len + 1) / 2;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t count = count_substrings(argv[1]);
    printf("%zu\n", count);

    return EXIT_SUCCESS;
}