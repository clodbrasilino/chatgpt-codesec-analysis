#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_quoted_values(const char *str, size_t *count)
{
    char **values = NULL;
    size_t num_values = 0;
    const char *start = str;

    if (str == NULL || count == NULL) {
        return NULL;
    }

    while (*start != '\0') {
        const char *end;
        size_t len;
        char *value;
        char **temp;

        start = strchr(start, '"');
        if (start == NULL) {
            break;
        }
        start++;

        end = strchr(start, '"');
        if (end == NULL) {
            break;
        }

        len = (size_t)(end - start);
        value = (char *)malloc(len + 1);
        if (value == NULL) {
            for (size_t i = 0; i < num_values; i++) {
                free(values[i]);
            }
            free(values);
            return NULL;
        }

        memcpy(value, start, len);
        value[len] = '\0';

        temp = (char **)realloc(values, (num_values + 1) * sizeof(char *));
        if (temp == NULL) {
            free(value);
            for (size_t i = 0; i < num_values; i++) {
                free(values[i]);
            }
            free(values);
            return NULL;
        }
        values = temp;
        values[num_values] = value;
        num_values++;

        start = end + 1;
    }

    *count = num_values;
    return values;
}

void free_quoted_values(char **values, size_t count)
{
    if (values == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(values[i]);
    }
    free(values);
}

int main(void)
{
    const char *input = "The quick \"brown\" fox jumps \"over\" the \"lazy\" dog";
    size_t count = 0;
    char **results = extract_quoted_values(input, &count);

    if (results == NULL && count > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Extracted %zu values:\n", count);
    for (size_t i = 0; i < count; i++) {
        printf("[%zu]: %s\n", i, results[i]);
    }

    free_quoted_values(results, count);
    return EXIT_SUCCESS;
}