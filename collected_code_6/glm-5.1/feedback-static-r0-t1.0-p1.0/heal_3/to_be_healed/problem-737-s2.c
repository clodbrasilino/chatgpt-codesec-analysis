#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int starts_with_vowel(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }

    char c = tolower((unsigned char)*str);
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
        return 1;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (starts_with_vowel(argv[1])) {
        printf("Starts with a vowel\n");
    } else {
        printf("Does not start with a vowel\n");
    }

    return EXIT_SUCCESS;
}