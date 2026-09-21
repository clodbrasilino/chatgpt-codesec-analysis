#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define LIST_SIZE 6

int convert_to_float_list(const char *list[], size_t size, float *results, size_t results_capacity, size_t *converted_count)
{
    size_t i;
    size_t count;
    char *endptr;
    float value;

    if (list == NULL || results == NULL || converted_count == NULL)
    {
        return -1;
    }

    if (size > results_capacity)
    {
        return -1;
    }

    count = 0;

    for (i = 0; i < size; i++)
    {
        if (list[i] == NULL)
        {
            results[i] = 0.0f;
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
        else
        {
            results[i] = 0.0f;
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
    const char *list[LIST_SIZE] = {"3.14", "-2.5", "abc", "42", "7.5e2", "hello"};
    float *results = NULL;
    size_t converted_count = 0;
    size_t list_size;
    size_t i;

    /* Possible weaknesses found:
     *  Assignment 'list_size=sizeof(list)/sizeof(list[0])', assigned value is 6
     */
    list_size = sizeof(list) / sizeof(list[0]);

    /* Possible weaknesses found:
     *  Condition 'list_size==0' is always false [knownConditionTrueFalse]
     *  Condition 'list_size==0' is always false
     */
    if (list_size == 0 || list_size > LIST_SIZE)
    {
        fprintf(stderr, "Error: invalid list size\n");
        return EXIT_FAILURE;
    }

    results = (float *)calloc(list_size, sizeof(*results));
    if (results == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (convert_to_float_list(list, list_size, results, list_size, &converted_count) != 0)
    {
        fprintf(stderr, "Error: invalid arguments\n");
        free(results);
        return EXIT_FAILURE;
    }

    for (i = 0; i < list_size; i++)
    {
        printf("Element %zu: %f\n", i, (double)results[i]);
    }

    printf("Total converted: %zu\n", converted_count);

    free(results);

    return EXIT_SUCCESS;
}