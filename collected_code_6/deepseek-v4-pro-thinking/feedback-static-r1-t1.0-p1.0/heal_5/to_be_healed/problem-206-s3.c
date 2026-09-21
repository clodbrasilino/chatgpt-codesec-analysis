#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concat_strings(const char *left, const char *right)
{
    if (left == NULL || right == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(left) + strlen(right);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(result, left);
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(result, right);
    return result;
}

char **adjacent_concatenate(const char **elements, size_t count, size_t *out_count)
{
    if (out_count == NULL) {
        return NULL;
    }

    *out_count = 0;

    if (elements == NULL || count < 2) {
        return NULL;
    }

    size_t result_count = count - 1;

    if (result_count > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    char **result = malloc(result_count * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t i;
    for (i = 0; i < result_count; i++) {
        result[i] = concat_strings(elements[i], elements[i + 1]);
        if (result[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
    }

    *out_count = result_count;
    return result;
}

int main(void)
{
    const char *data[] = {"GFG", "is", "best", "for", "geeks"};
    size_t count = sizeof(data) / sizeof(data[0]);
    size_t out_count = 0;
    char **result = adjacent_concatenate(data, count, &out_count);

    if (result == NULL) {
        return 1;
    }

    size_t i;
    for (i = 0; i < out_count; i++) {
        printf("%s\n", result[i]);
    }

    for (i = 0; i < out_count; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}