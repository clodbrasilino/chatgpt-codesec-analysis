#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096U

typedef enum {
    ITEM_INT,
    ITEM_STR
} ItemType;

typedef struct {
    ItemType type;
    union {
        long ival;
        char *sval;
    } data;
} Item;

static char *duplicate_string(const char *src)
{
    size_t len;
    size_t i;
    char *copy;

    if (src == NULL) {
        return NULL;
    }
    len = strnlen(src, MAX_STRING_LEN);
    if (len >= MAX_STRING_LEN) {
        return NULL;
    }
    copy = malloc(len + 1U);
    if (copy == NULL) {
        return NULL;
    }
    for (i = 0U; i < len; i++) {
        copy[i] = src[i];
    }
    copy[len] = '\0';
    return copy;
}

static int compare_items(const void *a, const void *b)
{
    const Item *ia = (const Item *)a;
    const Item *ib = (const Item *)b;

    if (ia->type != ib->type) {
        return (ia->type == ITEM_INT) ? -1 : 1;
    }
    if (ia->type == ITEM_INT) {
        if (ia->data.ival < ib->data.ival) {
            return -1;
        }
        if (ia->data.ival > ib->data.ival) {
            return 1;
        }
        return 0;
    }
    if (ia->data.sval == NULL || ib->data.sval == NULL) {
        if (ia->data.sval == ib->data.sval) {
            return 0;
        }
        return (ia->data.sval == NULL) ? -1 : 1;
    }
    return strcmp(ia->data.sval, ib->data.sval);
}

static void sort_mixed_list(Item *items, size_t count)
{
    if (items == NULL || count < 2U) {
        return;
    }
    qsort(items, count, sizeof(Item), compare_items);
}

static void free_items(Item *items, size_t count)
{
    size_t i;

    if (items == NULL) {
        return;
    }
    for (i = 0U; i < count; i++) {
        if (items[i].type == ITEM_STR) {
            free(items[i].data.sval);
            items[i].data.sval = NULL;
        }
    }
    free(items);
}

static int add_int(Item *items, size_t capacity, size_t index, long value)
{
    if (items == NULL || index >= capacity) {
        return -1;
    }
    items[index].type = ITEM_INT;
    items[index].data.ival = value;
    return 0;
}

static int add_str(Item *items, size_t capacity, size_t index, const char *value)
{
    char *copy;

    if (items == NULL || index >= capacity) {
        return -1;
    }
    copy = duplicate_string(value);
    if (copy == NULL) {
        return -1;
    }
    items[index].type = ITEM_STR;
    items[index].data.sval = copy;
    return 0;
}

static void print_items(const Item *items, size_t count)
{
    size_t i;

    if (items == NULL) {
        return;
    }
    for (i = 0U; i < count; i++) {
        if (items[i].type == ITEM_INT) {
            if (printf("%ld\n", items[i].data.ival) < 0) {
                return;
            }
        } else {
            if (items[i].data.sval != NULL) {
                if (printf("%s\n", items[i].data.sval) < 0) {
                    return;
                }
            }
        }
    }
}

int main(void)
{
    const size_t count = 7U;
    size_t filled = 0U;
    Item *items;

    items = calloc(count, sizeof(Item));
    if (items == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (add_int(items, count, filled, 42L) != 0) {
        free_items(items, filled);
        return EXIT_FAILURE;
    }
    filled++;

    if (add_str(items, count, filled, "banana") != 0) {
        free_items(items, filled);
        return EXIT_FAILURE;
    }
    filled++;

    if (add_int(items, count, filled, -7L) != 0) {
        free_items(items, filled);
        return EXIT_FAILURE;
    }
    filled++;

    if (add_str(items, count, filled, "apple") != 0) {
        free_items(items, filled);
        return EXIT_FAILURE;
    }
    filled++;

    if (add_int(items, count, filled, 13L) != 0) {
        free_items(items, filled);
        return EXIT_FAILURE;
    }
    filled++;

    if (add_str(items, count, filled, "cherry") != 0) {
        free_items(items, filled);
        return EXIT_FAILURE;
    }
    filled++;

    if (add_int(items, count, filled, 0L) != 0) {
        free_items(items, filled);
        return EXIT_FAILURE;
    }
    filled++;

    sort_mixed_list(items, filled);
    print_items(items, filled);
    free_items(items, filled);

    return EXIT_SUCCESS;
}