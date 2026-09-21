#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *extract_elements(const int *list, size_t list_size, size_t start, size_t count, size_t *extracted_size)
{
    int *result;

    if (list == NULL || extracted_size == NULL)
    {
        return NULL;
    }

    *extracted_size = 0;

    if (list_size == 0 || count == 0 || start >= list_size)
    {
        return NULL;
    }

    if (count > list_size - start)
    {
        return NULL;
    }

    result = (int *)malloc(count * sizeof(int));
    if (result == NULL)
    {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, list + start, count * sizeof(int));
    *extracted_size = count;

    return result;
}

int main(void)
{
    int list[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    size_t start = 3;
    size_t count = 4;
    size_t extracted_size = 0;
    size_t i;
    int *extracted;

    extracted = extract_elements(list, list_size, start, count, &extracted_size);
    if (extracted == NULL)
    {
        fprintf(stderr, "Extraction failed\n");
        return EXIT_FAILURE;
    }

    printf("Extracted elements:");
    for (i = 0; i < extracted_size; i++)
    {
        printf(" %d", extracted[i]);
    }
    printf("\n");

    free(extracted);
    extracted = NULL;

    return EXIT_SUCCESS;
}