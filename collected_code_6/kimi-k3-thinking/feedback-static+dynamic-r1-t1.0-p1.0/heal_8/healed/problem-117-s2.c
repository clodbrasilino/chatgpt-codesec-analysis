#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_STRING_LENGTH 128

static size_t bounded_strnlen(const char *s, size_t maxlen)
{
    size_t len;

    if (s == NULL)
    {
        return 0;
    }

    len = 0;
    while (len < maxlen && s[len] != '\0')
    {
        len++;
    }

    return len;
}

int convert_to_float_list(const char *list[], size_t size, float results[], size_t results_size, size_t *converted_count)
{
    size_t i;
    size_t count;
    char *endptr;
    float value;

    if (list == NULL || results == NULL || converted_count == NULL)
    {
        return -1;
    }

    if (size == 0 || size > results_size)
    {
        return -1;
    }

    count = 0;

    for (i = 0; i < size; i++)
    {
        size_t len;

        results[i] = 0.0f;

        if (list[i] == NULL)
        {
            continue;
        }

        len = bounded_strnlen(list[i], MAX_STRING_LENGTH);
        if (len == 0 || len >= MAX_STRING_LENGTH)
        {
            continue;
        }

        errno = 0;
        endptr = NULL;
        value = strtof(list[i], &endptr);

        if (endptr != list[i] && *endptr == '\0' && errno != ERANGE)
        {
            results[i] = value;
            count++;
        }
    }

    *converted_count = count;
    return 0;
}

int main(void)
{
    static const char *const raw_list[] = {"3.14", "-2.5", "abc", "42", "7.5e2", "hello"};
    const size_t list_size = sizeof(raw_list) / sizeof(raw_list[0]);
    char **list;
    const char **list_ptrs;
    float *results;
    size_t converted_count;
    size_t i;
    size_t j;

    converted_count = 0;

    list = calloc(list_size, sizeof(*list));
    if (list == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    list_ptrs = calloc(list_size, sizeof(*list_ptrs));
    if (list_ptrs == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        free(list);
        return EXIT_FAILURE;
    }

    results = calloc(list_size, sizeof(*results));
    if (results == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        free(list_ptrs);
        free(list);
        return EXIT_FAILURE;
    }

    for (i = 0; i < list_size; i++)
    {
        size_t len;
        size_t dest_size;
        size_t k;

        len = bounded_strnlen(raw_list[i], MAX_STRING_LENGTH);
        if (len == 0 || len >= MAX_STRING_LENGTH)
        {
            fprintf(stderr, "Error: string exceeds maximum length\n");
            for (j = 0; j < i; j++)
            {
                free(list[j]);
            }
            free(results);
            free(list_ptrs);
            free(list);
            return EXIT_FAILURE;
        }

        dest_size = len + 1;

        list[i] = malloc(dest_size);
        if (list[i] == NULL)
        {
            fprintf(stderr, "Error: memory allocation failed\n");
            for (j = 0; j < i; j++)
            {
                free(list[j]);
            }
            free(results);
            free(list_ptrs);
            free(list);
            return EXIT_FAILURE;
        }

        for (k = 0; k < len; k++)
        {
            list[i][k] = raw_list[i][k];
        }
        list[i][len] = '\0';

        list_ptrs[i] = list[i];
    }

    if (convert_to_float_list(list_ptrs, list_size, results, list_size, &converted_count) != 0)
    {
        fprintf(stderr, "Error: invalid arguments\n");
        for (i = 0; i < list_size; i++)
        {
            free(list[i]);
        }
        free(results);
        free(list_ptrs);
        free(list);
        return EXIT_FAILURE;
    }

    for (i = 0; i < list_size; i++)
    {
        printf("Element %zu: %f\n", i, (double)results[i]);
    }

    printf("Total converted: %zu\n", converted_count);

    for (i = 0; i < list_size; i++)
    {
        free(list[i]);
    }
    free(results);
    free(list_ptrs);
    free(list);

    return EXIT_SUCCESS;
}