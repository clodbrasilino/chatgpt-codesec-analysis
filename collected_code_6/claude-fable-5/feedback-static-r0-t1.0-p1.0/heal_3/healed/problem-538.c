#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define TUPLE_MAX_ITEM_LEN 4096U

typedef struct {
    char **items;
    size_t count;
} Tuple;

static Tuple *tuple_create(const char *const *list, size_t count);
static void tuple_destroy(Tuple *tuple);
static void tuple_print(const Tuple *tuple);

static Tuple *tuple_create(const char *const *list, size_t count)
{
    Tuple *tuple = NULL;
    size_t i = 0U;

    if (list == NULL || count == 0U) {
        return NULL;
    }

    if (count > (SIZE_MAX / sizeof(*tuple->items))) {
        return NULL;
    }

    tuple = malloc(sizeof(*tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = calloc(count, sizeof(*tuple->items));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }
    tuple->count = count;

    for (i = 0U; i < count; i++) {
        size_t len = 0U;
        size_t alloc_size = 0U;

        if (list[i] == NULL) {
            tuple_destroy(tuple);
            return NULL;
        }

        len = strnlen(list[i], TUPLE_MAX_ITEM_LEN);
        if (len >= TUPLE_MAX_ITEM_LEN) {
            tuple_destroy(tuple);
            return NULL;
        }

        alloc_size = len + 1U;
        tuple->items[i] = malloc(alloc_size);
        if (tuple->items[i] == NULL) {
            tuple_destroy(tuple);
            return NULL;
        }

        if (len > 0U) {
            memcpy(tuple->items[i], list[i], len);
        }
        tuple->items[i][len] = '\0';
    }

    return tuple;
}

static void tuple_destroy(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    if (tuple->items != NULL) {
        size_t i = 0U;

        for (i = 0U; i < tuple->count; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
    }
    free(tuple);
}

static void tuple_print(const Tuple *tuple)
{
    size_t i = 0U;

    if (tuple == NULL || tuple->items == NULL) {
        return;
    }

    if (printf("(") < 0) {
        return;
    }
    for (i = 0U; i < tuple->count; i++) {
        if (tuple->items[i] == NULL) {
            return;
        }
        if (printf("'%s'", tuple->items[i]) < 0) {
            return;
        }
        if (i + 1U < tuple->count) {
            if (printf(", ") < 0) {
                return;
            }
        }
    }
    if (printf(")\n") < 0) {
        return;
    }
}

int main(void)
{
    const char *const list[] = { "apple", "banana", "cherry", "date" };
    const size_t count = sizeof(list) / sizeof(list[0]);
    Tuple *tuple = NULL;

    tuple = tuple_create(list, count);
    if (tuple == NULL) {
        (void)fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    tuple_print(tuple);
    tuple_destroy(tuple);

    return EXIT_SUCCESS;
}