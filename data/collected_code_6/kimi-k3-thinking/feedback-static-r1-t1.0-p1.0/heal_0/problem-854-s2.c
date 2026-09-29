#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void swap_elements(int *first, int *second)
{
    int temporary = *first;
    *first = *second;
    *second = temporary;
}

static void sift_down(int *array, size_t heap_size, size_t root_index)
{
    size_t largest = root_index;

    for (;;)
    {
        size_t left_child = (2U * largest) + 1U;
        size_t right_child = (2U * largest) + 2U;
        size_t selected = largest;

        if (left_child < heap_size && array[left_child] > array[selected])
        {
            selected = left_child;
        }

        if (right_child < heap_size && array[right_child] > array[selected])
        {
            selected = right_child;
        }

        if (selected == largest)
        {
            break;
        }

        swap_elements(&array[largest], &array[selected]);
        largest = selected;
    }
}

int build_heap(int *array, size_t element_count)
{
    if (array == NULL)
    {
        return -1;
    }

    if (element_count < 2U)
    {
        return 0;
    }

    size_t index = element_count / 2U;

    while (index > 0U)
    {
        index--;
        sift_down(array, element_count, index);
    }

    return 0;
}

int main(void)
{
    const int initial_values[] = {9, 4, 7, 1, 8, 3, 6, 2, 5, 0};
    const size_t element_count = sizeof(initial_values) / sizeof(initial_values[0]);

    int *values = malloc(element_count * sizeof(*values));

    if (values == NULL)
    {
        fprintf(stderr, "Error: unable to allocate memory.\n");
        return EXIT_FAILURE;
    }

    memcpy(values, initial_values, element_count * sizeof(*values));

    if (build_heap(values, element_count) != 0)
    {
        fprintf(stderr, "Error: unable to build heap.\n");
        free(values);
        return EXIT_FAILURE;
    }

    printf("Heap contents:");

    for (size_t i = 0U; i < element_count; i++)
    {
        printf(" %d", values[i]);
    }

    printf("\n");

    free(values);
    values = NULL;

    return EXIT_SUCCESS;
}