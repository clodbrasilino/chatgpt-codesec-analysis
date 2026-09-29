#include <stdio.h>
#include <stdlib.h>

int *get_first_elements(int **sublists, const size_t *sublist_sizes, size_t num_sublists, size_t *out_count)
{
    if (sublists == NULL || sublist_sizes == NULL || out_count == NULL || num_sublists == 0)
    {
        return NULL;
    }

    int *first_elements = malloc(num_sublists * sizeof *first_elements);
    if (first_elements == NULL)
    {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < num_sublists; i++)
    {
        if (sublists[i] != NULL && sublist_sizes[i] > 0)
        {
            first_elements[count] = sublists[i][0];
            count++;
        }
    }

    *out_count = count;
    return first_elements;
}

int main(void)
{
    int sub1[] = {1, 2, 3};
    int sub2[] = {4, 5};
    int sub3[] = {6, 7, 8, 9};
    int sub4[] = {10};

    int *sublists[] = {sub1, sub2, sub3, sub4};
    /* Possible weaknesses found:
     *  Variable 'sublist_sizes' can be declared as const array [constVariable]
     */
    size_t sublist_sizes[] = {3, 2, 4, 1};
    size_t num_sublists = sizeof sublists / sizeof sublists[0];

    size_t count = 0;
    int *first_elements = get_first_elements(sublists, sublist_sizes, num_sublists, &count);

    if (first_elements == NULL)
    {
        fprintf(stderr, "Error: unable to retrieve first elements\n");
        return EXIT_FAILURE;
    }

    printf("First elements: ");
    for (size_t i = 0; i < count; i++)
    {
        printf("%d ", first_elements[i]);
    }
    printf("\n");

    free(first_elements);
    first_elements = NULL;

    return EXIT_SUCCESS;
}