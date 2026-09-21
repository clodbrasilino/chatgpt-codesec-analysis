#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_min_rotations(const char *str, size_t *result)
{
    size_t len;
    size_t i;
    char *temp;

    if (str == NULL || result == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    if (len == 0U) {
        return -1;
    }

    temp = (char *)malloc((2U * len) + 1U);
    if (temp == NULL) {
        return -1;
    }

    if (snprintf(temp, (2U * len) + 1U, "%s%s", str, str) < 0) {
        free(temp);
        return -1;
    }

    for (i = 1U; i <= len; i++) {
        if (strncmp(str, &temp[i], len) == 0) {
            *result = i;
            free(temp);
            return 0;
        }
    }

    free(temp);
    return -1;
}

int main(void)
{
    const char *input = "abcabc";
    size_t rotations = 0U;

    if (find_min_rotations(input, &rotations) == 0) {
        if (printf("Minimum rotations for \"%s\": %zu\n", input, rotations) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (fprintf(stderr, "Error: could not compute rotations\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}