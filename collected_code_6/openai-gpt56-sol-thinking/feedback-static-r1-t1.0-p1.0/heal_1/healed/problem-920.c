#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
    bool is_none;
} TupleValue;

typedef struct {
    TupleValue *values;
    size_t count;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
} TupleList;

static bool tuple_is_all_none(const Tuple *tuple)
{
    size_t i;

    for (i = 0; i < tuple->count; ++i) {
        if (!tuple->values[i].is_none) {
            return false;
        }
    }

    return true;
}

bool remove_all_none_tuples(TupleList *list)
{
    size_t read_index;
    size_t write_index;
    size_t original_count;

    if (list == NULL) {
        return false;
    }

    if (list->count > 0 && list->items == NULL) {
        return false;
    }

    for (read_index = 0; read_index < list->count; ++read_index) {
        if (list->items[read_index].count > 0 &&
            list->items[read_index].values == NULL) {
            return false;
        }
    }

    original_count = list->count;
    write_index = 0;

    for (read_index = 0; read_index < original_count; ++read_index) {
        if (!tuple_is_all_none(&list->items[read_index])) {
            if (write_index != read_index) {
                list->items[write_index] = list->items[read_index];
            }
            ++write_index;
        }
    }

    for (read_index = write_index; read_index < original_count; ++read_index) {
        list->items[read_index].values = NULL;
        list->items[read_index].count = 0;
    }

    list->count = write_index;
    return true;
}

int main(void)
{
    TupleValue first[] = {
        { true },
        { true }
    };
    TupleValue second[] = {
        { true },
        { false },
        { true }
    };
    TupleValue third[] = {
        { true }
    };
    TupleValue fourth[] = {
        { false },
        { false }
    };
    Tuple tuples[] = {
        { first, sizeof first / sizeof first[0] },
        { second, sizeof second / sizeof second[0] },
        { third, sizeof third / sizeof third[0] },
        { fourth, sizeof fourth / sizeof fourth[0] }
    };
    TupleList list = {
        tuples,
        sizeof tuples / sizeof tuples[0]
    };

    if (!remove_all_none_tuples(&list)) {
        return EXIT_FAILURE;
    }

    if (list.count != 2 ||
        list.items[0].values != second ||
        list.items[1].values != fourth) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}