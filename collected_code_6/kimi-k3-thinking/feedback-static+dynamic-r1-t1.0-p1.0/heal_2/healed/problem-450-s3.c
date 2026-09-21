#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

char **extract_strings(const char **list, size_t list_size, size_t extract_size, size_t *out_count);
void free_string_list(char **list, size_t count);

static size_t bounded_strlen(const char *s, size_t max_len, int *valid)
{
    const char *end;

    end = memchr(s, '\0', max_len);
    if (end == NULL) {
        *valid = 0;
        return 0;
    }

    *valid = 1;
    return (size_t)(end - s);
}

char **extract_strings(const char **list, size_t list_size, size_t extract_size, size_t *out_count)
{
    char **result;
    size_t count;
    size_t i;
    size_t j;

    if (out_count == NULL) {
        return NULL;
    }
    *out_count = 0;

    if (list == NULL) {
        return NULL;
    }

    count = 0;
    for (i = 0; i < list_size; i++) {
        size_t len;
        int valid;

        if (list[i] == NULL) {
            return NULL;
        }

        len = bounded_strlen(list[i], MAX_STRING_LENGTH, &valid);
        if (!valid) {
            return NULL;
        }

        if (len == extract_size) {
            count++;
        }
    }

    if (count > SIZE_MAX / sizeof(*result)) {
        return NULL;
    }

    result = malloc((count > 0 ? count : 1) * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < list_size && j < count; i++) {
        size_t len;
        int valid;

        len = bounded_strlen(list[i], MAX_STRING_LENGTH, &valid);
        if (!valid || len != extract_size) {
            continue;
        }

        result[j] = malloc(len + 1);
        if (result[j] == NULL) {
            free_string_list(result, j);
            return NULL;
        }

        memcpy(result[j], list[i], len + 1);
        j++;
    }

    *out_count = count;
    return result;
}

void free_string_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

static int run_case(const char **list, size_t list_size, size_t extract_size)
{
    char **extracted;
    size_t extracted_count = 0;
    size_t i;

    extracted = extract_strings(list, list_size, extract_size, &extracted_count);
    if (extracted == NULL) {
        fprintf(stderr, "String extraction failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < extracted_count; i++) {
        if (printf("%s\n", extracted[i]) < 0) {
            fprintf(stderr, "Output error\n");
            free_string_list(extracted, extracted_count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(extracted, extracted_count);
    return EXIT_SUCCESS;
}

int main(void)
{
    const char *list0[] = {"practice", "makes", "perfect", "solution"};
    const char *list1[] = {"Python", "is", "fun"};
    const char *list2[] = {"coding", "exercises", "are", "fun"};

    if (run_case(list0, sizeof(list0) / sizeof(list0[0]), 8) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    if (run_case(list1, sizeof(list1) / sizeof(list1[0]), 6) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    if (run_case(list2, sizeof(list2) / sizeof(list2[0]), 9) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}