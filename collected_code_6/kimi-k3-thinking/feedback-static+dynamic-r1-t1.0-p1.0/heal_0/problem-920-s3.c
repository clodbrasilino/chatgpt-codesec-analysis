#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#define TUPLE_SIZE 3

typedef struct {
    int values[TUPLE_SIZE];
    bool is_none[TUPLE_SIZE];
} Tuple;

static bool tuple_all_none(const Tuple *t)
{
    size_t i;

    if (t == NULL) {
        return false;
    }

    for (i = 0; i < TUPLE_SIZE; i++) {
        if (!t->is_none[i]) {
            return false;
        }
    }
    return true;
}

size_t remove_all_none_tuples(Tuple *tuples, size_t count)
{
    size_t read_index;
    size_t write_index;

    if (tuples == NULL) {
        return 0;
    }

    write_index = 0;
    for (read_index = 0; read_index < count; read_index++) {
        if (!tuple_all_none(&tuples[read_index])) {
            if (write_index != read_index) {
                tuples[write_index] = tuples[read_index];
            }
            write_index++;
        }
    }
    return write_index;
}

static void print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;
    size_t j;

    if (tuples == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        printf("(");
        for (j = 0; j < TUPLE_SIZE; j++) {
            if (tuples[i].is_none[j]) {
                printf("None");
            } else {
                printf("%d", tuples[i].values[j]);
            }
            if (j + 1 < TUPLE_SIZE) {
                printf(", ");
            }
        }
        printf(")\n");
    }
}

int main(void)
{
    Tuple tuples[] = {
        {{1, 2, 3}, {false, false, false}},
        {{0, 0, 0}, {true, true, true}},
        {{4, 5, 6}, {false, false, false}},
        {{0, 0, 0}, {true, true, true}},
        {{7, 8, 9}, {false, true, false}}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t new_count;

    printf("Original tuples:\n");
    print_tuples(tuples, count);

    new_count = remove_all_none_tuples(tuples, count);

    printf("\nAfter removing all-None tuples:\n");
    print_tuples(tuples, new_count);

    return 0;
}