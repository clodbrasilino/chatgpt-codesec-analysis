#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    const int *elements;
    size_t length;
} Tuple;

int *tuple_intersection(const Tuple *tuples, size_t num_tuples, size_t *out_size)
{
    if (out_size == NULL) return NULL;
    *out_size = 0;
    if (tuples == NULL || num_tuples == 0) return NULL;

    size_t first_len = tuples[0].length;
    const int *first = tuples[0].elements;

    if (first == NULL && first_len > 0) return NULL;
    if (first_len > SIZE_MAX / sizeof(int)) return NULL;

    int *result = malloc(first_len * sizeof(int));
    if (result == NULL && first_len > 0) return NULL;

    size_t res_count = 0;

    for (size_t i = 0; i < first_len; ++i)
    {
        int candidate = first[i];

        int duplicate = 0;
        for (size_t k = 0; k < res_count; ++k)
        {
            if (result[k] == candidate)
            {
                duplicate = 1;
                break;
            }
        }

        if (duplicate) continue;

        int present_in_all = 1;

        for (size_t t = 1; t < num_tuples; ++t)
        {
            if (tuples[t].elements == NULL && tuples[t].length > 0)
            {
                free(result);
                return NULL;
            }

            int found = 0;
            for (size_t j = 0; j < tuples[t].length; ++j)
            {
                if (tuples[t].elements[j] == candidate)
                {
                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                present_in_all = 0;
                break;
            }
        }

        if (present_in_all)
        {
            result[res_count++] = candidate;
        }
    }

    if (res_count == 0)
    {
        free(result);
        return NULL;
    }

    int *shrunk = realloc(result, res_count * sizeof(int));
    if (shrunk == NULL)
    {
        free(result);
        return NULL;
    }

    *out_size = res_count;
    return shrunk;
}

int main(void)
{
    int a1[] = {1, 2, 3, 2};
    int a2[] = {2, 3, 4};
    int a3[] = {3, 2, 5};

    Tuple tuples[] = {
        {a1, sizeof(a1) / sizeof(a1[0])},
        {a2, sizeof(a2) / sizeof(a2[0])},
        {a3, sizeof(a3) / sizeof(a3[0])}
    };

    size_t out_size = 0;
    int *intersection = tuple_intersection(tuples, 3, &out_size);

    if (intersection != NULL)
    {
        for (size_t i = 0; i < out_size; ++i)
        {
            printf("%d ", intersection[i]);
        }
        printf("\n");
        free(intersection);
    }
    else
    {
        printf("No intersection or error\n");
    }

    return 0;
}