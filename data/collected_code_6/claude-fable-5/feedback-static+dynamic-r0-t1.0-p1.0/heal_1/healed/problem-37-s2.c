#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096U

typedef enum {
    ITEM_INT,
    ITEM_STR
} ItemType;

typedef struct {
    ItemType type;
    union {
        long num;
        char *str;
    } value;
} Item;

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }
    len = strnlen(src, MAX_STR_LEN);
    if (len >= MAX_STR_LEN) {
        return NULL;
    }
    copy = malloc(len + 1U);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, src, len);
    copy[len] = '\0';
    return copy;
}

static int compare_items(const void *a, const void *b)
{
    const Item *left = (const Item *)a;
    const Item *right = (const Item *)b;

    if (left->type != right->type) {
        return (left->type == ITEM_INT) ? -1 : 1;
    }
    if (left->type == ITEM_INT) {
        if (left->value.num < right->value.num) {
            return -1;
        }
        if (left->value.num > right->value.num) {
            return 1;
        }
        return 0;
    }
    if (left->value.str == NULL || right->value.str == NULL) {
        if (left->value.str == right->value.str) {
            return 0;
        }
        return (left->value.str == NULL) ? -1 : 1;
    }
    return strcmp(left->value.str, right->value.str);
}

static void free_items(Item *items, size_t count)
{
    size_t i;

    if (items == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        if (items[i].type == ITEM_STR) {
            free(items[i].value.str);
            items[i].value.str = NULL;
        }
    }
    free(items);
}

static int sort_mixed_list(Item *items, size_t count)
{
    if (items == NULL || count == 0U) {
        return -1;
    }
    qsort(items, count, sizeof(Item), compare_items);
    return 0;
}

static int add_int_item(Item *items, size_t index, size_t capacity, long value)
{
    if (items == NULL || index >= capacity) {
        return -1;
    }
    items[index].type = ITEM_INT;
    items[index].value.num = value;
    return 0;
}

static int add_str_item(Item *items, size_t index, size_t capacity, const char *value)
{
    char *copy;

    if (items == NULL || value == NULL || index >= capacity) {
        return -1;
    }
    copy = duplicate_string(value);
    if (copy == NULL) {
        return -1;
    }
    items[index].type = ITEM_STR;
    items[index].value.str = copy;
    return 0;
}

static void print_items(const Item *items, size_t count)
{
    size_t i;

    if (items == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        if (items[i].type == ITEM_INT) {
            if (printf("%ld\n", items[i].value.num) < 0) {
                return;
            }
        } else {
            if (items[i].value.str != NULL) {
                if (printf("%s\n", items[i].value.str) < 0) {
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

    if (add_int_item(items, filled, count, 42L) != 0) {
        free_items(items, filled);
        return EXIT_FAILURE;
    }
    filled++;

    if (add_str_item(items, filled, count, "banana") != 0) {
        free_items(items, filled);
        return EXIT_FAILURE;
    }
    filled++;

    if (add_int_item(items, filled, count, -7L) != 0) {
        free_items(items, filled);
        return EXIT_FAILURE;
    }
    filled++;

    if (add_str_item(items, filled, count, "apple") != 0) {
        free_items(items, filled);
        return EXIT_FAILURE;
    }
    filled++;

    if (add_int_item(items, filled, count, 15L) != 0) {
        free_items(items, filled);
        return EXIT_FAILURE;
    }
    filled++;

    if (add_str_item(items, filled, count, "cherry") != 0) {
        free_items(items, filled);
        return EXIT_FAILURE;
    }
    filled++;

    if (add_int_item(items, filled, count, 0L) != 0) {
        free_items(items, filled);
        return EXIT_FAILURE;
    }
    filled++;

    if (sort_mixed_list(items, filled) != 0) {
        fprintf(stderr, "Sorting failed\n");
        free_items(items, filled);
        return EXIT_FAILURE;
    }

    print_items(items, filled);
    free_items(items, filled);
    return EXIT_SUCCESS;
}