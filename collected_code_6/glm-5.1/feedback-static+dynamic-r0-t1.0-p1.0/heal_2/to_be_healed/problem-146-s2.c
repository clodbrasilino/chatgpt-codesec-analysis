#include <stdio.h>
#include <stdlib.h>

size_t find_total_ascii(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t total = 0;
    size_t i = 0;

    while (str[i] != '\0') {
        total += (unsigned char)str[i];
        i++;
    }

    return total;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t result = find_total_ascii(argv[1]);
    printf("%zu\n", result);

    return EXIT_SUCCESS;
}