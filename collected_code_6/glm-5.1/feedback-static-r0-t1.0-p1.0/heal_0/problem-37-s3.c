#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_STRING
} ItemType;

typedef struct {
    ItemType type;
    union {
        int int_val;
        char *str_val;
    } data;
} ListItem;

void free_list(ListItem *list, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (list[i].type == TYPE_STRING && list[i].data.str_val != NULL) {
            free(list[i].data.str_val);
        }
    }
    free(list);
}

int compare_items(const void *a, const void *b) {
    const ListItem *ia = (const ListItem *)a;
    const ListItem *ib = (const ListItem *)b;

    if (ia->type == TYPE_INT && ib->type == TYPE_INT) {
        if (ia->data.int_val < ib->data.int_val) return -1;
        if (ia->data.int_val > ib->data.int_val) return 1;
        return 0;
    }

    if (ia->type == TYPE_STRING && ib->type == TYPE_STRING) {
        return strcmp(ia->data.str_val, ib->data.str_val);
    }

    if (ia->type == TYPE_INT) {
        return -1;
    }

    return 1;
}

void sort_mixed_list(ListItem *list, size_t size) {
    if (list == NULL || size == 0) {
        return;
    }
    qsort(list, size, sizeof(ListItem), compare_items);
}

int main(void) {
    size_t size = 5;
    ListItem *list = malloc(size * sizeof(ListItem));
    if (list == NULL) {
        return 1;
    }

    list[0].type = TYPE_STRING;
    list[0].data.str_val = strdup("hello");
    if (list[0].data.str_val == NULL) {
        free(list);
        return 1;
    }

    list[1].type = TYPE_INT;
    list[1].data.int_val = 42;

    list[2].type = TYPE_STRING;
    list[2].data.str_val = strdup("world");
    if (list[2].data.str_val == NULL) {
        free(list[0].data.str_val);
        free(list);
        return 1;
    }

    list[3].type = TYPE_INT;
    list[3].data.int_val = -5;

    list[4].type = TYPE_STRING;
    list[4].data.str_val = strdup("abc");
    if (list[4].data.str_val == NULL) {
        free(list[0].data.str_val);
        free(list[2].data.str_val);
        free(list);
        return 1;
    }

    sort_mixed_list(list, size);

    for (size_t i = 0; i < size; i++) {
        if (list[i].type == TYPE_INT) {
            printf("%d\n", list[i].data.int_val);
        } else if (list[i].type == TYPE_STRING) {
            printf("%s\n", list[i].data.str_val);
        }
    }

    free_list(list, size);

    return 0;
}