#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>

#define MAX_NAME_LEN 50
#define MAX_TUPLE_COUNT 1000000

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    float value;
} Tuple;

static bool safe_string_copy(char *dest, size_t dest_size, const char *src)
{
    size_t src_len;
    size_t i;

    if (dest == NULL || src == NULL || dest_size == 0) {
        return false;
    }

    src_len = 0;
    while (src_len < dest_size && src[src_len] != '\0') {
        src_len++;
    }

    if (src_len >= dest_size) {
        dest[0] = '\0';
        return false;
    }

    for (i = 0; i <= src_len; i++) {
        dest[i] = src[i];
    }

    return true;
}

static bool validate_tuple(const Tuple *tuple)
{
    size_t i;
    bool has_null;

    if (tuple == NULL) {
        return false;
    }

    has_null = false;
    for (i = 0; i < MAX_NAME_LEN; i++) {
        if (tuple->name[i] == '\0') {
            has_null = true;
            break;
        }
    }

    return has_null;
}

int rearrange_tuples(Tuple *tuples, size_t tuple_count, const size_t *order, size_t order_count)
{
    Tuple *temp;
    size_t i;
    size_t j;

    if (tuples == NULL || order == NULL) {
        return -1;
    }

    if (tuple_count == 0 || order_count == 0) {
        return -1;
    }

    if (tuple_count > MAX_TUPLE_COUNT) {
        return -1;
    }

    if (order_count > tuple_count) {
        return -1;
    }

    if (tuple_count > SIZE_MAX / sizeof(Tuple)) {
        return -1;
    }

    for (i = 0; i < tuple_count; i++) {
        if (!validate_tuple(&tuples[i])) {
            return -1;
        }
    }

    for (i = 0; i < order_count; i++) {
        if (order[i] >= tuple_count) {
            return -1;
        }
    }

    temp = (Tuple *)calloc(tuple_count, sizeof(Tuple));
    if (temp == NULL) {
        return -1;
    }

    for (i = 0; i < order_count; i++) {
        temp[i].id = tuples[order[i]].id;
        temp[i].value = tuples[order[i]].value;
        if (!safe_string_copy(temp[i].name, MAX_NAME_LEN, tuples[order[i]].name)) {
            free(temp);
            temp = NULL;
            return -1;
        }
    }

    for (i = 0; i < order_count; i++) {
        tuples[i].id = temp[i].id;
        tuples[i].value = temp[i].value;
        for (j = 0; j < MAX_NAME_LEN; j++) {
            tuples[i].name[j] = temp[i].name[j];
        }
    }

    free(temp);
    temp = NULL;

    return 0;
}

void print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;

    if (tuples == NULL || count == 0) {
        return;
    }

    if (count > MAX_TUPLE_COUNT) {
        return;
    }

    for (i = 0; i < count; i++) {
        if (validate_tuple(&tuples[i])) {
            printf("Tuple %zu: id=%d, name=%.49s, value=%.2f\n",
                   i, tuples[i].id, tuples[i].name, tuples[i].value);
        }
    }
}

static bool init_tuple(Tuple *tuple, int id, const char *name, float value)
{
    if (tuple == NULL || name == NULL) {
        return false;
    }

    tuple->id = id;
    tuple->value = value;

    if (!safe_string_copy(tuple->name, MAX_NAME_LEN, name)) {
        return false;
    }

    return true;
}

int main(void)
{
    Tuple tuples[5];
    size_t order[] = {2, 0, 4, 1, 3};
    size_t tuple_count;
    size_t order_count;
    int result;
    bool init_ok;

    init_ok = true;
    init_ok = init_ok && init_tuple(&tuples[0], 1, "Alpha", 10.5f);
    init_ok = init_ok && init_tuple(&tuples[1], 2, "Beta", 20.3f);
    init_ok = init_ok && init_tuple(&tuples[2], 3, "Gamma", 30.7f);
    init_ok = init_ok && init_tuple(&tuples[3], 4, "Delta", 40.1f);
    init_ok = init_ok && init_tuple(&tuples[4], 5, "Epsilon", 50.9f);

    if (!init_ok) {
        fprintf(stderr, "Error: Failed to initialize tuples\n");
        return EXIT_FAILURE;
    }

    tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    order_count = sizeof(order) / sizeof(order[0]);

    printf("Original tuples:\n");
    print_tuples(tuples, tuple_count);

    result = rearrange_tuples(tuples, tuple_count, order, order_count);

    if (result != 0) {
        fprintf(stderr, "Error: Failed to rearrange tuples\n");
        return EXIT_FAILURE;
    }

    printf("\nRearranged tuples:\n");
    print_tuples(tuples, tuple_count);

    return EXIT_SUCCESS;
}