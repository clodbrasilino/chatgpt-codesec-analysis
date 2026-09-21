#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096
#define MAX_ITEM_SIZE (1024u * 1024u)

typedef struct {
    void **items;
    size_t *sizes;
    size_t count;
} Tuple;

Tuple *tuple_create(size_t count)
{
    Tuple *t = NULL;

    if (count == 0 || count > SIZE_MAX / sizeof(void *)) {
        return NULL;
    }

    t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    t->items = calloc(count, sizeof(void *));
    if (t->items == NULL) {
        free(t);
        return NULL;
    }

    t->sizes = calloc(count, sizeof(size_t));
    if (t->sizes == NULL) {
        free(t->items);
        free(t);
        return NULL;
    }

    t->count = count;
    return t;
}

int tuple_set_item(Tuple *t, size_t index, const void *data, size_t size)
{
    void *copy = NULL;

    if (t == NULL || data == NULL || size == 0 || size > MAX_ITEM_SIZE) {
        return -1;
    }

    if (index >= t->count) {
        return -1;
    }

    copy = malloc(size);
    if (copy == NULL) {
        return -1;
    }

    memcpy(copy, data, size);

    free(t->items[index]);
    t->items[index] = copy;
    t->sizes[index] = size;

    return 0;
}

const void *tuple_get_item(const Tuple *t, size_t index, size_t *size_out)
{
    if (t == NULL) {
        return NULL;
    }

    if (index >= t->count) {
        return NULL;
    }

    if (size_out != NULL) {
        *size_out = t->sizes[index];
    }

    return t->items[index];
}

void tuple_destroy(Tuple *t)
{
    size_t i;

    if (t == NULL) {
        return;
    }

    for (i = 0; i < t->count; i++) {
        free(t->items[i]);
    }

    free(t->items);
    free(t->sizes);
    free(t);
}

int main(void)
{
    Tuple *t = NULL;
    int number = 42;
    double value = 3.14;
    const char *text = "hello";
    const void *item = NULL;
    size_t size = 0;
    size_t text_len = 0;

    t = tuple_create(3);
    if (t == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    if (tuple_set_item(t, 0, &number, sizeof(number)) != 0) {
        fprintf(stderr, "Failed to set item 0\n");
        tuple_destroy(t);
        return EXIT_FAILURE;
    }

    if (tuple_set_item(t, 1, &value, sizeof(value)) != 0) {
        fprintf(stderr, "Failed to set item 1\n");
        tuple_destroy(t);
        return EXIT_FAILURE;
    }

    text_len = strnlen(text, MAX_STRING_LEN);
    if (text_len >= MAX_STRING_LEN) {
        fprintf(stderr, "String too long or not terminated\n");
        tuple_destroy(t);
        return EXIT_FAILURE;
    }

    if (tuple_set_item(t, 2, text, text_len + 1) != 0) {
        fprintf(stderr, "Failed to set item 2\n");
        tuple_destroy(t);
        return EXIT_FAILURE;
    }

    item = tuple_get_item(t, 0, &size);
    if (item != NULL && size == sizeof(int)) {
        printf("Item 0: %d\n", *(const int *)item);
    }

    item = tuple_get_item(t, 1, &size);
    if (item != NULL && size == sizeof(double)) {
        printf("Item 1: %f\n", *(const double *)item);
    }

    item = tuple_get_item(t, 2, &size);
    if (item != NULL && size > 0 && ((const char *)item)[size - 1] == '\0') {
        printf("Item 2: %s\n", (const char *)item);
    }

    item = tuple_get_item(t, 5, &size);
    if (item == NULL) {
        printf("Index 5 is out of bounds\n");
    }

    tuple_destroy(t);
    return EXIT_SUCCESS;
}