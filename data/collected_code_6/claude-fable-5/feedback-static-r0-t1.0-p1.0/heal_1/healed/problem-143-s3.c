#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef enum ElementType
{
    ELEMENT_INT,
    ELEMENT_LIST
} ElementType;

typedef struct Element
{
    ElementType type;
    union
    {
        int int_value;
        struct
        {
            const int *items;
            size_t count;
        } list_value;
    } data;
} Element;

typedef struct Tuple
{
    const Element *elements;
    size_t count;
} Tuple;

static int count_lists(const Tuple *tuple, size_t *result)
{
    size_t i;
    size_t total;

    if (tuple == NULL || result == NULL)
    {
        return -1;
    }

    if (tuple->count > 0U && tuple->elements == NULL)
    {
        return -1;
    }

    total = 0U;
    for (i = 0U; i < tuple->count; i++)
    {
        if (tuple->elements[i].type == ELEMENT_LIST)
        {
            total++;
        }
    }

    *result = total;
    return 0;
}

static int sum_list_items(const Tuple *tuple, long *result)
{
    size_t i;
    size_t j;
    long total;

    if (tuple == NULL || result == NULL)
    {
        return -1;
    }

    if (tuple->count > 0U && tuple->elements == NULL)
    {
        return -1;
    }

    total = 0L;
    for (i = 0U; i < tuple->count; i++)
    {
        if (tuple->elements[i].type == ELEMENT_LIST)
        {
            const int *items = tuple->elements[i].data.list_value.items;
            size_t count = tuple->elements[i].data.list_value.count;

            if (count > 0U && items == NULL)
            {
                return -1;
            }

            for (j = 0U; j < count; j++)
            {
                total += (long)items[j];
            }
        }
        else
        {
            total += (long)tuple->elements[i].data.int_value;
        }
    }

    *result = total;
    return 0;
}

int main(void)
{
    static const int list_a[] = {1, 2, 3};
    static const int list_b[] = {4, 5};
    static const int list_c[] = {6};

    static const Element elements_one[] = {
        { ELEMENT_LIST, { .list_value = { list_a, 3U } } },
        { ELEMENT_INT,  { .int_value = 10 } },
        { ELEMENT_LIST, { .list_value = { list_b, 2U } } }
    };

    static const Element elements_two[] = {
        { ELEMENT_INT,  { .int_value = 7 } },
        { ELEMENT_INT,  { .int_value = 8 } },
        { ELEMENT_LIST, { .list_value = { list_c, 1U } } }
    };

    static const Element elements_three[] = {
        { ELEMENT_INT, { .int_value = 1 } },
        { ELEMENT_INT, { .int_value = 2 } }
    };

    Tuple tuples[3];
    size_t list_count;
    long sum;
    size_t i;

    tuples[0].elements = elements_one;
    tuples[0].count = sizeof(elements_one) / sizeof(elements_one[0]);
    tuples[1].elements = elements_two;
    tuples[1].count = sizeof(elements_two) / sizeof(elements_two[0]);
    tuples[2].elements = elements_three;
    tuples[2].count = sizeof(elements_three) / sizeof(elements_three[0]);

    for (i = 0U; i < 3U; i++)
    {
        if (count_lists(&tuples[i], &list_count) != 0)
        {
            fprintf(stderr, "Error: invalid tuple input\n");
            return EXIT_FAILURE;
        }

        if (sum_list_items(&tuples[i], &sum) != 0)
        {
            fprintf(stderr, "Error: invalid tuple input\n");
            return EXIT_FAILURE;
        }

        printf("Tuple %zu contains %zu list(s), total value %ld\n",
               i + 1U, list_count, sum);
    }

    return EXIT_SUCCESS;
}