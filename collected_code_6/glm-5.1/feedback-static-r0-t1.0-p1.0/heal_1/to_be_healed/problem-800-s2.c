#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char* remove_whitespaces(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    for (const char* p = str; *p; p++) {
        if (!isspace((unsigned char)*p)) {
            len++;
        }
    }

    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    char* dest = result;
    for (const char* src = str; *src; src++) {
        if (!isspace((unsigned char)*src)) {
            *dest++ = *src;
        }
    }

    *dest = '\0';
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char* cleaned = remove_whitespaces(argv[1]);
    if (cleaned == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", cleaned);

    free(cleaned);
    return EXIT_SUCCESS;
}