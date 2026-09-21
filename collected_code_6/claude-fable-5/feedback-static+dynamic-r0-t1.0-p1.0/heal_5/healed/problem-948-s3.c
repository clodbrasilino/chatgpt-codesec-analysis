#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_ITEM_SIZE 4096U
#define MAX_STRING_LEN 256U
#define MAX_TUPLE_COUNT 1024U

typedef struct {
    void **items;
    size_t *sizes;
    size_t count;
} Tuple;

static int safe_copy(void *dest, size_t dest_size, const void *src, size_t src_size)
{
    unsigned char *d;
    const unsigned char *s;
    size_t i;

    if ((dest == NULL) || (src == NULL)) {
        return -1;
    }
    if ((src_size == 0U) || (src_size > dest_size)) {
        return -1;
    }

    d = (unsigned char *)dest;
    s = (const unsigned char *)src;
    for (i = 0U; i < src_size; i++) {
        d[i] = s[i];
    }
    return 0;
}

Tuple *tuple_create(size_t count)
{
    Tuple *t;

    if ((count == 0U) || (count > MAX_TUPLE_COUNT)) {
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

    if (safe_copy(copy, size, data, size) != 0) {
        free(copy);
        return -1;
    }

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
        t->items[i] = NULL;
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

static int is_valid_string_item(const void *item, size_t size)
{
    const char *str;

    if ((item == NULL) || (size == 0U) || (size > MAX_ITEM_SIZE)) {
        return 0;
    }
    str = (const char *)item;
    if (str[size - 1U] != '\0') {
        return 0;
    }
    if (bounded_strlen(str, size) != (size - 1U)) {
        return 0;
    }
    return 1;
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
        int value;
        if (safe_copy(&value, sizeof(value), item, size) == 0) {
            printf("Item 0: %d (size %zu)\n", value, size);
        }
    }

    item = tuple_get_item(t, 1U, &size);
    if ((item != NULL) && (size == sizeof(double))) {
        double value;
        if (safe_copy(&value, sizeof(value), item, size) == 0) {
            printf("Item 1: %f (size %zu)\n", value, size);
        }
    }

    item = tuple_get_item(t, 2U, &size);
    if (is_valid_string_item(item, size)) {
        printf("Item 2: %s (size %zu)\n", (const char *)item, size);
    }

    item = tuple_get_item(t, 5U, &size);
    if (item == NULL) {
        printf("Item 5: out of range\n");
    }

    tuple_destroy(t);
    return EXIT_SUCCESS;
}