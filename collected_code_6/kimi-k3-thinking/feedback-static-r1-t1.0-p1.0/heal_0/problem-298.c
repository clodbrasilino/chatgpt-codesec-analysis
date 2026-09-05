#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int is_present(const int *list, size_t size, int value)
{
    size_t i;

    for (i = 0; i < size; i++)
    {
        if (list[i] == value)
        {
            return 1;
        }
    }

    return 0;
}

static int find_nested_in_list(const int *const *nested, size_t rows,
                               const size_t *cols,
                               const int *list, size_t list_size,
                               int **out, size_t *out_size)
{
    int *result = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t i;
    size_t j;

    if (out == NULL || out_size == NULL)
    {
        return -1;
    }

    *out = NULL;
    *out_size = 0;

    if (nested == NULL || cols == NULL || list == NULL)
    {
        return -1;
    }

    for (i = 0; i < rows; i++)
    {
        if (nested[i] == NULL)
        {
            continue;
        }

        for (j = 0; j < cols[i]; j++)
        {
            if (!is_present(list, list_size, nested[i][j]))
            {
                continue;
            }

            if (count == capacity)
            {
                size_t new_capacity;
                int *tmp;

                if (capacity == 0)
                {
                    new_capacity = 8;
                }
                else
                {
                    if (capacity > SIZE_MAX / 2)
                    {
                        free(result);
                        return -1;
                    }
                    new_capacity = capacity * 2;
                }

                if (new_capacity > SIZE_MAX / sizeof(int))
                {
                    free(result);
                    return -1;
                }

                tmp = realloc(result, new_capacity * sizeof(int));
                if (tmp == NULL)
                {
                    free(result);
                    return -1;
                }

                result = tmp;
                capacity = new_capacity;
            }

            result[count] = nested[i][j];
            count++;
        }
    }

    if (count == 0)
    {
        free(result);
        result = NULL;
    }

    *out = result;
    *out_size = count;
    return 0;
}

int main(void)
{
    int row0[] = {1, 2, 3};
    int row1[] = {4, 5};
    int row2[] = {6, 7, 8, 9};
    const int *nested[] = {row0, row1, row2};
    size_t cols[] = {3, 2, 4};
    int list[] = {2, 5, 7, 9, 12};
    size_t rows = sizeof(nested) / sizeof(nested[0]);
    size_t list_size = sizeof(list) / sizeof(list[0]);
    int *matches = NULL;
    size_t match_count = 0;
    size_t i;

    if (find_nested_in_list(nested, rows, cols, list, list_size,
                            &matches, &match_count) != 0)
    {
        fprintf(stderr, "Error: unable to search the nested list.\n");
        free(matches);
        return EXIT_FAILURE;
    }

    if (match_count == 0)
    {
        printf("No nested list elements are present in the list.\n");
    }
    else
    {
        printf("Nested list elements present in the list: ");
        for (i = 0; i < match_count; i++)
        {
            printf("%d%s", matches[i], (i + 1 < match_count) ? ", " : "\n");
        }
    }

    free(matches);
    return EXIT_SUCCESS;
}