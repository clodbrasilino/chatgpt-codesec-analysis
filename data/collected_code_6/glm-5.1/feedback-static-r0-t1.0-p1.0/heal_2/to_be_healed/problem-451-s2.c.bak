#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_whitespaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t res_idx = 0;
    const char *p = str;

    while (*p) {
        if (!isspace((unsigned char)*p)) {
            result[res_idx++] = *p;
        }
        p++;
    }

    result[res_idx] = '\0';

    char *shrunk = realloc(result, res_idx + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *cleaned = remove_whitespaces(argv[1]);
    if (cleaned == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", cleaned);
    free(cleaned);
    return EXIT_SUCCESS;
}