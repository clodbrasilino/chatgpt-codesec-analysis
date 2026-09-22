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
    size_t extracted;

    if (out_count == NULL) {
        return NULL;
    }

    *out_count = 0;

    if (strings == NULL || count == 0) {
        return NULL;
    }

    result = calloc(count, sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    extracted = 0;

    for (i = 0; i < count; i++) {
        size_t len;
        size_t k;

        if (strings[i] == NULL) {
            continue;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        len = strlen(strings[i]);

        if (len != size) {
            continue;
        }

        result[extracted] = malloc(len + 1);
        if (result[extracted] == NULL) {
            free_strings(result, count);
            *out_count = 0;
            return NULL;
        }

        for (k = 0; k < len; k++) {
            result[extracted][k] = strings[i][k];
        }
        result[extracted][len] = '\0';

        extracted++;
    }

    *out_count = extracted;

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
    const size_t extract_size = 6;
    size_t extracted_count = 0;
    char **extracted;
    size_t i;

    extracted = extract_strings(values, count, extract_size, &extracted_count);
    if (extracted == NULL) {
        fprintf(stderr, "Failed to extract strings\n");
        return EXIT_FAILURE;
    }

    printf("Extracted %zu strings of size %zu:\n", extracted_count, extract_size);
    for (i = 0; i < extracted_count; i++) {
        if (extracted[i] != NULL) {
            printf("[%zu] %s\n", i, extracted[i]);
        }
    }

    free_strings(extracted, count);

    return EXIT_SUCCESS;
}