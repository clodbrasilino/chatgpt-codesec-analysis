#include <stdio.h>
#include <stdlib.h>

unsigned long get_total_ascii(const char *str) {
    if (str == NULL) {
        return 0;
    }
    unsigned long total = 0;
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
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    unsigned long result = get_total_ascii(argv[1]);
    printf("%lu\n", result);
    return EXIT_SUCCESS;
}