#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_first_repeated(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    size_t len = strlen(str);
    if (len == 0) {
        return '\0';
    }

    int *char_count = (int *)calloc(256, sizeof(int));
    if (char_count == NULL) {
        return '\0';
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (char_count[c] > 0) {
            free(char_count);
            return str[i];
        }
        char_count[c]++;
    }

    free(char_count);
    return '\0';
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char result = find_first_repeated(argv[1]);
    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("No repeated character found\n");
    }

    return EXIT_SUCCESS;
}