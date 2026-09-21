#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096U

typedef enum { ITEM_INT, ITEM_STR } ItemType;

typedef struct {
    ItemType type;
    union {
        int num;
        char *str;
    } value;
} Item;

static int compare_items(const void *a, const void *b)
{
    const Item *x = (const Item *)a;
    const Item *y = (const Item *)b;

    if (x->type == ITEM_INT && y->type == ITEM_INT) {
        if (x->value.num < y->value.num) {
            return -1;
        }
        if (x->value.num > y->value.num) {
            return 1;
        }
        return 0;
    }
    if (x->type == ITEM_STR && y->type == ITEM_STR) {
        return strcmp(x->value.str, y->value.str);
    }
    return (x->type == ITEM_INT) ? -1 : 1;
}

void sort_mixed_list(Item *items, size_t count)
{
    if (items != NULL && count > 1U) {
        qsort(items, count, sizeof(Item), compare_items);
    }
}

static int set_int_item(Item *item, int value)
{
    if (item == NULL) {
        return -1;
    }
    item->type = ITEM_INT;
    item->value.num = value;
    return 0;
}

static int set_str_item(Item *item, const char *text)
{
    size_t len;
    size_t buf_size;
    char *copy;

    if (item == NULL || text == NULL) {
        return -1;
    }
    len = strnlen(text, MAX_STR_LEN);
    if (len >= MAX_STR_LEN) {
        return -1;
    }
    buf_size = len + 1U;
    copy = (char *)malloc(buf_size);
    if (copy == NULL) {
        return -1;
    }
    if (len > 0U) {
        memcpy(copy, text, len);
    }
    copy[len] = '\0';
    item->type = ITEM_STR;
    item->value.str = copy;
    return 0;
}

static void free_items(Item *items, size_t count)
{
    size_t i;

    if (items == NULL) {
        return;
    }
    for (i = 0U; i < count; i++) {
        if (items[i].type == ITEM_STR) {
            free(items[i].value.str);
            items[i].value.str = NULL;
        }
    }
}

static void print_items(const Item *items, size_t count)
{
    size_t i;

    if (items == NULL) {
        return;
    }
    for (i = 0U; i < count; i++) {
        if (items[i].type == ITEM_INT) {
            (void)printf("%d\n", items[i].value.num);
        } else {
            (void)printf("%s\n", items[i].value.str);
        }
    }
}

int main(void)
{
    Item items[8];
    size_t count = 0U;
    int status = EXIT_SUCCESS;

    if (set_int_item(&items[count], 42) != 0) { goto cleanup_fail; }
    count++;
    if (set_str_item(&items[count], "banana") != 0) { goto cleanup_fail; }
    count++;
    if (set_int_item(&items[count], 7) != 0) { goto cleanup_fail; }
    count++;
    if (set_str_item(&items[count], "apple") != 0) { goto cleanup_fail; }
    count++;
    if (set_int_item(&items[count], -3) != 0) { goto cleanup_fail; }
    count++;
    if (set_str_item(&items[count], "cherry") != 0) { goto cleanup_fail; }
    count++;
    if (set_int_item(&items[count], 100) != 0) { goto cleanup_fail; }
    count++;
    if (set_str_item(&items[count], "apricot") != 0) { goto cleanup_fail; }
    count++;

    (void)printf("Before sorting:\n");
    print_items(items, count);

    sort_mixed_list(items, count);

    (void)printf("After sorting:\n");
    print_items(items, count);

    free_items(items, count);
    return status;

cleanup_fail:
    (void)fprintf(stderr, "Memory allocation failed\n");
    free_items(items, count);
    return EXIT_FAILURE;
}