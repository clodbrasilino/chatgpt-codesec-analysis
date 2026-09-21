#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate_road(const char *input)
{
    const char *pattern = "road";
    const char *replacement = "rd.";
    size_t pattern_len;
    size_t replacement_len;
    size_t count;
    size_t result_len;
    const char *p;
    char *result;
    char *dest;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    pattern_len = strlen(pattern);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    replacement_len = strlen(replacement);
    count = 0;

    p = input;
    while ((p = strstr(p, pattern)) != NULL) {
        count++;
        p += pattern_len;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    result_len = strlen(input) + count * replacement_len;
    if (count * pattern_len > result_len) {
        return NULL;
    }
    result_len -= count * pattern_len;

    result = malloc(result_len + 1);
    if (result == NULL) {
        return NULL;
    }

    dest = result;
    p = input;
    while (*p != '\0') {
        if (strncmp(p, pattern, pattern_len) == 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(dest, replacement, replacement_len);
            dest += replacement_len;
            p += pattern_len;
        } else {
            *dest = *p;
            dest++;
            p++;
        }
    }
    *dest = '\0';

    return result;
}

int main(void)
{
    const char *text = "Take the main road until the road forks near Elm road.";
    char *abbreviated;

    abbreviated = abbreviate_road(text);
    if (abbreviated == NULL) {
        fprintf(stderr, "Failed to abbreviate string\n");
        return EXIT_FAILURE;
    }

    if (printf("Original:    %s\n", text) < 0) {
        free(abbreviated);
        return EXIT_FAILURE;
    }

    if (printf("Abbreviated: %s\n", abbreviated) < 0) {
        free(abbreviated);
        return EXIT_FAILURE;
    }

    free(abbreviated);
    return EXIT_SUCCESS;
}