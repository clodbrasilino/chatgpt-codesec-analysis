#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 4096

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

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && s[len] != '\0') {
        len++;
    }

    return len;
}

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

        if (strings[i] == NULL) {
            continue;
        }

        len = bounded_strlen(strings[i], MAX_STRING_LENGTH);

        if (len == MAX_STRING_LENGTH || len < size) {
            continue;
        }

        result[extracted] = malloc(len + 1);
        if (result[extracted] == NULL) {
            free_strings(result, count);
            *out_count = 0;
            return NULL;
        }

        snprintf(result[extracted], len + 1, "%s", strings[i]);

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

    printf("Extracted %zu strings with at least %zu characters:\n", extracted_count, extract_size);
    for (i = 0; i < extracted_count; i++) {
        if (extracted[i] != NULL) {
            printf("[%zu] %s\n", i, extracted[i]);
        }
    }

    free_strings(extracted, count);

    return EXIT_SUCCESS;
}