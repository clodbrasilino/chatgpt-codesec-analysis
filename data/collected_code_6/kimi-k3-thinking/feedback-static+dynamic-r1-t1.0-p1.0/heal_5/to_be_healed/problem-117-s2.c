#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define LIST_SIZE 6
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

static int bounded_string_copy(char *dst, size_t dst_size, const char *src)
{
    size_t len;
    size_t i;

    if (dst == NULL || src == NULL || dst_size == 0)
    {
        return -1;
    }

    len = bounded_strnlen(src, dst_size - 1);

    for (i = 0; i < len; i++)
    {
        dst[i] = src[i];
    }
    dst[len] = '\0';

    if (src[len] != '\0')
    {
        return -1;
    }

    return 0;
}

int convert_to_float_list(const char *list[], size_t size, float results[], size_t results_size, size_t *converted_count)
{
    size_t i;
    size_t count;
    char *endptr;
    float value;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_STRING_LENGTH];

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
        results[i] = 0.0f;

        if (list[i] == NULL)
        {
            continue;
        }

        if (bounded_string_copy(buffer, sizeof(buffer), list[i]) != 0)
        {
            continue;
        }

        errno = 0;
        endptr = NULL;
        value = strtof(buffer, &endptr);

        if (endptr != buffer && *endptr == '\0' && errno != ERANGE)
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    static const char *const raw_list[LIST_SIZE] = {"3.14", "-2.5", "abc", "42", "7.5e2", "hello"};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char list[LIST_SIZE][MAX_STRING_LENGTH];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *list_ptrs[LIST_SIZE];
    float *results;
    size_t converted_count;
    size_t i;

    converted_count = 0;

    memset(list, 0, sizeof(list));

    for (i = 0; i < LIST_SIZE; i++)
    {
        int written = snprintf(list[i], MAX_STRING_LENGTH, "%s", raw_list[i]);
        if (written < 0 || (size_t)written >= MAX_STRING_LENGTH)
        {
            fprintf(stderr, "Error: string exceeds maximum length\n");
            return EXIT_FAILURE;
        }
        list[i][MAX_STRING_LENGTH - 1] = '\0';
        list_ptrs[i] = list[i];
    }

    results = calloc(LIST_SIZE, sizeof(*results));
    if (results == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (convert_to_float_list(list_ptrs, LIST_SIZE, results, LIST_SIZE, &converted_count) != 0)
    {
        fprintf(stderr, "Error: invalid arguments\n");
        free(results);
        return EXIT_FAILURE;
    }

    for (i = 0; i < LIST_SIZE; i++)
    {
        printf("Element %zu: %f\n", i, (double)results[i]);
    }

    printf("Total converted: %zu\n", converted_count);

    free(results);
    return EXIT_SUCCESS;
}