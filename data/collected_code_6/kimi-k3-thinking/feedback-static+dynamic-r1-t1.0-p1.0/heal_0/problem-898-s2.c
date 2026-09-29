#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int *extract_elements(const int *list, size_t list_size, size_t start, size_t count, size_t *out_size)
{
    int *result;
    size_t i;

    if (list == NULL || out_size == NULL)
    {
        return NULL;
    }

    if (start >= list_size || count == 0 || count > list_size - start)
    {
        *out_size = 0;
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(*result))
    {
        *out_size = 0;
        return NULL;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL)
    {
        *out_size = 0;
        return NULL;
    }

    for (i = 0; i < count; i++)
    {
        result[i] = list[start + i];
    }

    *out_size = count;
    return result;
}

int main(void)
{
    int list[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    size_t start = 2;
    size_t count = 4;
    size_t out_size = 0;
    size_t i;
    int *extracted;

    extracted = extract_elements(list, list_size, start, count, &out_size);
    if (extracted == NULL)
    {
        fprintf(stderr, "Error: unable to extract elements.\n");
        return EXIT_FAILURE;
    }

    printf("Extracted elements: ");
    for (i = 0; i < out_size; i++)
    {
        printf("%d ", extracted[i]);
    }
    printf("\n");

    free(extracted);
    extracted = NULL;

    return EXIT_SUCCESS;
}