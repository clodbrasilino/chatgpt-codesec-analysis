#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEM_SIZE 4096U
#define MAX_STRING_LEN 256U

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

    if ((t == NULL) || (data == NULL) || (size == 0U) || (size > MAX_ITEM_SIZE)) {
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

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len = 0U;

    if (s == NULL) {
        return 0U;
    }
    while ((len < max_len) && (s[len] != '\0')) {
        len++;
    }
    return len;
}

int main(void)
{
    Tuple *t;
    int number = 42;
    double pi = 3.14159;
    const char *text = "hello";
    const void *item;
    size_t size;
    size_t text_len;

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

    text_len = bounded_strlen(text, MAX_STRING_LEN);
    if (text_len >= MAX_STRING_LEN) {
        fprintf(stderr, "String too long or not terminated\n");
        tuple_destroy(t);
        return EXIT_FAILURE;
    }
    if (tuple_set_item(t, 2U, text, text_len + 1U) != 0) {
        fprintf(stderr, "Failed to set item 2\n");
        tuple_destroy(t);
        return EXIT_FAILURE;
    }

    item = tuple_get_item(t, 0U, &size);
    if ((item != NULL) && (size == sizeof(int))) {
        printf("Item 0: %d (size %zu)\n", *(const int *)item, size);
    }

    item = tuple_get_item(t, 1U, &size);
    if ((item != NULL) && (size == sizeof(double))) {
        printf("Item 1: %f (size %zu)\n", *(const double *)item, size);
    }

    item = tuple_get_item(t, 2U, &size);
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    if ((item != NULL) && (size > 0U) && (((const char *)item)[size - 1U] == '\0')) {
        printf("Item 2: %s (size %zu)\n", (const char *)item, size);
    }

    item = tuple_get_item(t, 5U, &size);
    if (item == NULL) {
        printf("Item 5: out of range\n");
    }

    tuple_destroy(t);
    return EXIT_SUCCESS;
}