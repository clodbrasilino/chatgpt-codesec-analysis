#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_strings(char **strings, size_t count)
{
    size_t i;

    if (strings == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 2 failed: expected ['exercises'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  */

char **extract_strings(const char *const *strings, size_t count, size_t size, size_t *out_count)
{
    char **result;
    size_t i;

    if (strings == NULL || out_count == NULL || count == 0) {
        return NULL;
    }

    *out_count = 0;

    result = calloc(count, sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t len;

        if (strings[i] == NULL) {
            continue;
        }

        len = strnlen(strings[i], size);

        result[i] = malloc(len + 1);
        if (result[i] == NULL) {
            free_strings(result, count);
            *out_count = 0;
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[i], strings[i], len);
        result[i][len] = '\0';
        (*out_count)++;
    }

    return result;
}

int main(void)
{
    const char *values[] = {
        "apple",
        "banana",
        "cherry",
        "dragonfruit",
        "elderberry"
    };
    const size_t count = sizeof(values) / sizeof(values[0]);
    const size_t extract_size = 4;
    size_t extracted_count = 0;
    char **extracted;
    size_t i;

    extracted = extract_strings(values, count, extract_size, &extracted_count);
    if (extracted == NULL) {
        fprintf(stderr, "Failed to extract strings\n");
        return EXIT_FAILURE;
    }

    printf("Extracted %zu strings of size %zu:\n", extracted_count, extract_size);
    for (i = 0; i < count; i++) {
        if (extracted[i] != NULL) {
            printf("[%zu] %s\n", i, extracted[i]);
        }
    }

    free_strings(extracted, count);

    return EXIT_SUCCESS;
}