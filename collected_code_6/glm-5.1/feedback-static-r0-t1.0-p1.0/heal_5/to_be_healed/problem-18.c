#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_chars(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(str2);
    char* lookup = calloc(256, sizeof(char));
    if (lookup == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len2; i++) {
        unsigned char c = str2[i];
        lookup[c] = 1;
    }

    char* result = malloc(len1 + 1);
    if (result == NULL) {
        free(lookup);
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len1; i++) {
        unsigned char c = str1[i];
        if (!lookup[c]) {
            result[j++] = c;
        }
    }
    result[j] = '\0';

    free(lookup);
    return result;
}

int main(int argc, char* const * argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", argv[0]);
        return 1;
    }

    char* filtered = remove_chars(argv[1], argv[2]);
    if (filtered == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("%s\n", filtered);
    free(filtered);
    return 0;
}