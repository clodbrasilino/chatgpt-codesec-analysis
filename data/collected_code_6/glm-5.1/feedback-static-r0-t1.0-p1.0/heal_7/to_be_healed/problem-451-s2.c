#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_whitespaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t argv_len = strlen(argv[1]);
    char *safe_arg = malloc(argv_len + 1);
    if (safe_arg == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(safe_arg, argv[1], argv_len + 1);

    char *cleaned = remove_whitespaces(safe_arg);
    free(safe_arg);

    if (cleaned == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", cleaned);
    free(cleaned);
    return EXIT_SUCCESS;
}