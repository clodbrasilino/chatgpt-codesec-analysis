#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'GoogleDart', got <no output>
  *  test case 0 failed: expected 'GoogleFlutter', got <no output>
  *  test case 2 failed: expected 'iOSSwift', got <no output>
  */

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
    for (size_t i = 0; i < len; i++) {
        if (!isspace((unsigned char)str[i])) {
            result[res_idx++] = str[i];
        }
    }

    result[res_idx] = '\0';

    char *shrunk = realloc(result, res_idx + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(int argc, char const * const argv[]) {
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