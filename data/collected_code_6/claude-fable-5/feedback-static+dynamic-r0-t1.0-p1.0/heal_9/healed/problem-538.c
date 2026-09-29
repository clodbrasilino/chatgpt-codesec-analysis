#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

static Tuple *tuple_create(const char *const *list, size_t count);
static void tuple_destroy(Tuple *tuple);
static void tuple_print(const Tuple *tuple);
static char *string_duplicate(const char *src);

static char *string_duplicate(const char *src)
{
    size_t len;
    size_t alloc_size;
    char *dst = NULL;

    if (src == NULL) {
        return NULL;
    }

    len = strnlen(src, SIZE_MAX - 1U);
    if (len >= SIZE_MAX - 1U) {
        return NULL;
    }

    alloc_size = len + 1U;
    if (alloc_size <= len) {
        return NULL;
    }

    dst = malloc(alloc_size);
    if (dst == NULL) {
        return NULL;
    }

    if (len > 0U) {
        (void)memcpy(dst, src, len);
    }
    dst[len] = '\0';

    return dst;
}

static Tuple *tuple_create(const char *const *list, size_t count)
{
    Tuple *tuple = NULL;

    if (list == NULL || count == 0U) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(*tuple->items)) {
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

    for (size_t i = 0U; i < count; i++) {
        tuple->items[i] = string_duplicate(list[i]);
        if (tuple->items[i] == NULL) {
            tuple_destroy(tuple);
            return NULL;
        }
    }

    return tuple;
}

static void tuple_destroy(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    if (tuple->items != NULL) {
        for (size_t i = 0U; i < tuple->count; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
    }
    free(tuple);
}

static void tuple_print(const Tuple *tuple)
{
    if (tuple == NULL || tuple->items == NULL) {
        return;
    }

    if (printf("(") < 0) {
        return;
    }
    for (size_t i = 0U; i < tuple->count; i++) {
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