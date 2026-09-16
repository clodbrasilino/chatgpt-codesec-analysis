#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
} TupleSet;

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;

    if (a->first < b->first) {
        return -1;
    }
    if (a->first > b->first) {
        return 1;
    }
    if (a->second < b->second) {
        return -1;
    }
    if (a->second > b->second) {
        return 1;
    }
    return 0;
}

static TupleSet *tuples_to_set(const Tuple *tuples, size_t count)
{
    TupleSet *set;
    size_t read_index;
    size_t write_index;

    if (count > 0 && tuples == NULL) {
        errno = EINVAL;
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        errno = EOVERFLOW;
        return NULL;
    }

    set = malloc(sizeof(*set));
    if (set == NULL) {
        return NULL;
    }

    set->items = NULL;
    set->count = 0;

    if (count == 0) {
        return set;
    }

    set->items = malloc(count * sizeof(*set->items));
    if (set->items == NULL) {
        free(set);
        return NULL;
    }

    for (read_index = 0; read_index < count; ++read_index) {
        set->items[read_index] = tuples[read_index];
    }

    qsort(set->items, count, sizeof(*set->items), compare_tuples);

    write_index = 1;
    for (read_index = 1; read_index < count; ++read_index) {
        if (compare_tuples(&set->items[read_index],
                           &set->items[write_index - 1]) != 0) {
            set->items[write_index] = set->items[read_index];
            ++write_index;
        }
    }

    set->count = write_index;
    return set;
}

static void tuple_set_destroy(TupleSet *set)
{
    if (set != NULL) {
        free(set->items);
        free(set);
    }
}

static int print_tuple_set(const TupleSet *set)
{
    size_t index;

    if (set == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (fputc('{', stdout) == EOF) {
        return -1;
    }

    for (index = 0; index < set->count; ++index) {
        if (index > 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (printf("(%d, %d)",
                   set->items[index].first,
                   set->items[index].second) < 0) {
            return -1;
        }
    }

    if (fputs("}\n", stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    const Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {1, 2},
        {5, 6},
        {3, 4},
        {7, 8}
    };
    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    TupleSet *set;
    int result;

    set = tuples_to_set(tuples, tuple_count);
    if (set == NULL) {
        perror("tuples_to_set");
        return EXIT_FAILURE;
    }

    result = print_tuple_set(set);
    tuple_set_destroy(set);

    if (result != 0) {
        perror("print_tuple_set");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}