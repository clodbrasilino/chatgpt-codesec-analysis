#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t strnlen_safe(const char *s, size_t maxlen)
{
    size_t i;
    for (i = 0; i < maxlen && s[i] != '\0'; i++)
        ;
    return i;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['exercises'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  */

char **extract_strings(const char *input[], size_t count, size_t target_len, size_t *out_count)
{
    char **result;
    size_t i;
    size_t j;
    size_t len;
    char *copy;

    if (input == NULL || out_count == NULL) {
        return NULL;
    }

    if (count >= ((size_t)-1) / sizeof(char *)) {
        return NULL;
    }

    result = malloc((count + 1) * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < count; i++) {
        if (input[i] == NULL) {
            continue;
        }

        len = strnlen_safe(input[i], target_len + 1);
        if (len != target_len) {
            continue;
        }

        copy = malloc(len + 1);
        if (copy == NULL) {
            size_t k;
            for (k = 0; k < j; k++) {
                free(result[k]);
            }
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, input[i], len + 1);
        result[j++] = copy;
    }

    result[j] = NULL;
    *out_count = j;
    return result;
}

void free_strings(char **strings)
{
    size_t i;

    if (strings == NULL) {
        return;
    }

    for (i = 0; strings[i] != NULL; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main(void)
{
    const char *input[] = {"hello", "world", "C", "code", "test"};
    size_t count = sizeof(input) / sizeof(input[0]);
    size_t out_count = 0;
    size_t i;
    char **result;

    result = extract_strings(input, count, 5, &out_count);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < out_count; i++) {
        printf("%s\n", result[i]);
    }

    free_strings(result);
    return EXIT_SUCCESS;
}