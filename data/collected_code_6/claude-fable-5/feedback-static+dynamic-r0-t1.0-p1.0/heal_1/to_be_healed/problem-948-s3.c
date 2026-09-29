#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void **items;
    size_t *sizes;
    size_t count;
} Tuple;

Tuple *tuple_create(size_t count)
{
    Tuple *t;

    if (count == 0U) {
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
    void *copy;

    if ((t == NULL) || (data == NULL) || (size == 0U)) {
        return -1;
    }
    if (index >= t->count) {
        return -1;
    }

    copy = malloc(size);
    if (copy == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
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
    if (t->items[index] == NULL) {
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
    for (i = 0U; i < t->count; i++) {
        free(t->items[i]);
    }
    free(t->items);
    free(t->sizes);
    free(t);
}

int main(void)
{
    Tuple *t;
    int number = 42;
    double pi = 3.14159;
    const char *text = "hello";
    const void *item;
    size_t size;

    t = tuple_create(3U);
    if (t == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    if (tuple_set_item(t, 0U, &number, sizeof(number)) != 0) {
        fprintf(stderr, "Failed to set item 0\n");
        tuple_destroy(t);
        return EXIT_FAILURE;
    }
    if (tuple_set_item(t, 1U, &pi, sizeof(pi)) != 0) {
        fprintf(stderr, "Failed to set item 1\n");
        tuple_destroy(t);
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (tuple_set_item(t, 2U, text, strlen(text) + 1U) != 0) {
        fprintf(stderr, "Failed to set item 2\n");
        tuple_destroy(t);
        return EXIT_FAILURE;
    }

    item = tuple_get_item(t, 0U, &size);
    if (item != NULL) {
        printf("Item 0: %d (size %zu)\n", *(const int *)item, size);
    }

    item = tuple_get_item(t, 1U, &size);
    if (item != NULL) {
        printf("Item 1: %f (size %zu)\n", *(const double *)item, size);
    }

    item = tuple_get_item(t, 2U, &size);
    if (item != NULL) {
        printf("Item 2: %s (size %zu)\n", (const char *)item, size);
    }

    item = tuple_get_item(t, 5U, &size);
    if (item == NULL) {
        printf("Item 5: out of range\n");
    }

    tuple_destroy(t);
    return EXIT_SUCCESS;
}