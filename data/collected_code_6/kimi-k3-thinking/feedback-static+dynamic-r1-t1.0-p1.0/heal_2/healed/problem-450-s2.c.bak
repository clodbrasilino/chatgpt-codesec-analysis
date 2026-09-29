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

char **extract_strings(const char *const *strings, size_t count, size_t size, size_t *out_count)
{
    char **result;
    size_t i;

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

    for (i = 0; i < count; i++) {
        size_t len;

        if (strings[i] == NULL) {
            continue;
        }

        len = strlen(strings[i]);
        if (len != size) {
            continue;
        }

        result[*out_count] = malloc(len + 1);
        if (result[*out_count] == NULL) {
            free_strings(result, *out_count);
            return NULL;
        }

        memcpy(result[*out_count], strings[i], len + 1);
        (*out_count)++;
    }

    return result;
}

int is_number(const char *s)
{
    if (s == NULL || *s == '\0') {
        return 0;
    }

    while (*s != '\0') {
        if (*s < '0' || *s > '9') {
            return 0;
        }
        s++;
    }

    return 1;
}

int main(void)
{
    char **values = NULL;
    size_t count = 0;
    size_t capacity = 0;
    char buffer[4096];
    char **extracted = NULL;
    size_t extracted_count = 0;
    size_t size = 0;
    size_t start = 0;
    size_t string_count = 0;
    size_t i;
    int size_found = 0;

    while (scanf("%4095s", buffer) == 1) {
        char *copy;

        if (count == capacity) {
            size_t new_capacity = (capacity == 0) ? 8 : capacity * 2;
            char **new_values = realloc(values, new_capacity * sizeof(*new_values));
            if (new_values == NULL) {
                free_strings(values, count);
                return EXIT_FAILURE;
            }
            values = new_values;
            capacity = new_capacity;
        }

        copy = malloc(strlen(buffer) + 1);
        if (copy == NULL) {
            free_strings(values, count);
            return EXIT_FAILURE;
        }
        strcpy(copy, buffer);
        values[count++] = copy;
    }

    if (count > 0 && is_number(values[count - 1])) {
        size = (size_t)strtoull(values[count - 1], NULL, 10);
        start = 0;
        string_count = count - 1;
        size_found = 1;
    } else if (count > 0 && is_number(values[0])) {
        size = (size_t)strtoull(values[0], NULL, 10);
        start = 1;
        string_count = count - 1;
        size_found = 1;
    }

    if (size_found && string_count > 0) {
        extracted = extract_strings((const char *const *)(values + start), string_count, size, &extracted_count);
        if (extracted == NULL) {
            free_strings(values, count);
            return EXIT_FAILURE;
        }
    }

    printf("[");
    for (i = 0; i < extracted_count; i++) {
        printf("%s'%s'", (i == 0) ? "" : ", ", extracted[i]);
    }
    printf("]\n");

    free_strings(extracted, extracted_count);
    free_strings(values, count);

    return EXIT_SUCCESS;
}