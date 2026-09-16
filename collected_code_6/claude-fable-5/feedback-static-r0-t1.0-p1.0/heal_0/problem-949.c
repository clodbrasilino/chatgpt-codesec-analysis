#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int count_digits(int value)
{
    int count;
    unsigned int magnitude;

    if (value < 0) {
        magnitude = (unsigned int)(-(long)value);
    } else {
        magnitude = (unsigned int)value;
    }

    count = 1;
    while (magnitude >= 10U) {
        magnitude /= 10U;
        count++;
    }
    return count;
}

static int total_digits(const Tuple *t)
{
    return count_digits(t->first) + count_digits(t->second);
}

static int compare_tuples(const void *a, const void *b)
{
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    int da = total_digits(ta);
    int db = total_digits(tb);

    if (da < db) {
        return -1;
    }
    if (da > db) {
        return 1;
    }
    return 0;
}

static int sort_tuples_by_digits(Tuple *list, size_t count)
{
    if (list == NULL || count == 0U) {
        return -1;
    }
    qsort(list, count, sizeof(Tuple), compare_tuples);
    return 0;
}

static void print_tuples(const Tuple *list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }
    printf("[");
    for (i = 0U; i < count; i++) {
        printf("(%d, %d)", list[i].first, list[i].second);
        if (i + 1U < count) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    Tuple data[] = {
        {3, 4},
        {12, 6},
        {1234, 5678},
        {1, 2},
        {100, 20}
    };
    size_t count = sizeof(data) / sizeof(data[0]);

    printf("Before sorting: ");
    print_tuples(data, count);

    if (sort_tuples_by_digits(data, count) != 0) {
        fprintf(stderr, "Error: invalid input to sort function\n");
        return EXIT_FAILURE;
    }

    printf("After sorting:  ");
    print_tuples(data, count);

    return EXIT_SUCCESS;
}