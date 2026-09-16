#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *items;
    size_t length;
} IntList;

typedef struct
{
    const IntList **lists;
    size_t count;
    size_t max_length;
} MaxResult;

static int find_max_length_lists(const IntList *lists, size_t num_lists, MaxResult *result)
{
    size_t i;
    size_t max_len = 0U;
    size_t count = 0U;
    const IntList **matches = NULL;

    if ((lists == NULL) || (result == NULL) || (num_lists == 0U))
    {
        return -1;
    }

    for (i = 0U; i < num_lists; i++)
    {
        if (lists[i].length > max_len)
        {
            max_len = lists[i].length;
        }
    }

    for (i = 0U; i < num_lists; i++)
    {
        if (lists[i].length == max_len)
        {
            count++;
        }
    }

    matches = malloc(count * sizeof(const IntList *));
    if (matches == NULL)
    {
        return -1;
    }

    count = 0U;
    for (i = 0U; i < num_lists; i++)
    {
        if (lists[i].length == max_len)
        {
            matches[count] = &lists[i];
            count++;
        }
    }

    result->lists = matches;
    result->count = count;
    result->max_length = max_len;
    return 0;
}

static void free_max_result(MaxResult *result)
{
    if (result != NULL)
    {
        free((void *)result->lists);
        result->lists = NULL;
        result->count = 0U;
        result->max_length = 0U;
    }
}

static void print_list(const IntList *list)
{
    size_t i;

    if (list == NULL)
    {
        return;
    }

    (void)printf("[");
    for (i = 0U; i < list->length; i++)
    {
        if (i > 0U)
        {
            (void)printf(", ");
        }
        (void)printf("%d", list->items[i]);
    }
    (void)printf("]\n");
}

int main(void)
{
    int a[] = {1, 2, 3};
    int b[] = {4, 5};
    int c[] = {6, 7, 8};
    int d[] = {9};
    IntList lists[4];
    MaxResult result;
    size_t i;

    lists[0].items = a;
    lists[0].length = sizeof(a) / sizeof(a[0]);
    lists[1].items = b;
    lists[1].length = sizeof(b) / sizeof(b[0]);
    lists[2].items = c;
    lists[2].length = sizeof(c) / sizeof(c[0]);
    lists[3].items = d;
    lists[3].length = sizeof(d) / sizeof(d[0]);

    result.lists = NULL;
    result.count = 0U;
    result.max_length = 0U;

    if (find_max_length_lists(lists, sizeof(lists) / sizeof(lists[0]), &result) != 0)
    {
        (void)fprintf(stderr, "Failed to find lists with maximum length\n");
        return EXIT_FAILURE;
    }

    (void)printf("Maximum length: %zu\n", result.max_length);
    for (i = 0U; i < result.count; i++)
    {
        print_list(result.lists[i]);
    }

    free_max_result(&result);
    return EXIT_SUCCESS;
}