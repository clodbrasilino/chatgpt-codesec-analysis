#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
} IntList;

typedef struct {
    IntList *items;
    size_t size;
} ListOfLists;

void int_list_init(IntList *list)
{
    if (list == NULL) {
        return;
    }
    list->data = NULL;
    list->size = 0;
}

int int_list_assign(IntList *list, const int *values, size_t count)
{
    int *new_data;

    if (list == NULL) {
        return -1;
    }
    if (count > 0 && values == NULL) {
        return -1;
    }

    new_data = NULL;
    if (count > 0) {
        if (count > SIZE_MAX / sizeof(*new_data)) {
            return -1;
        }
        new_data = malloc(count * sizeof(*new_data));
        if (new_data == NULL) {
            return -1;
        }
        for (size_t i = 0; i < count; i++) {
            new_data[i] = values[i];
        }
    }

    free(list->data);
    list->data = new_data;
    list->size = count;
    return 0;
}

void int_list_free(IntList *list)
{
    if (list == NULL) {
        return;
    }
    free(list->data);
    list->data = NULL;
    list->size = 0;
}

void list_of_lists_init(ListOfLists *lol)
{
    if (lol == NULL) {
        return;
    }
    lol->items = NULL;
    lol->size = 0;
}

int list_of_lists_push(ListOfLists *lol, const int *values, size_t count)
{
    IntList *new_items;
    size_t new_size;

    if (lol == NULL) {
        return -1;
    }
    if (count > 0 && values == NULL) {
        return -1;
    }
    if (lol->size == SIZE_MAX) {
        return -1;
    }

    new_size = lol->size + 1;
    if (new_size > SIZE_MAX / sizeof(*new_items)) {
        return -1;
    }

    new_items = realloc(lol->items, new_size * sizeof(*new_items));
    if (new_items == NULL) {
        return -1;
    }
    lol->items = new_items;

    int_list_init(&lol->items[lol->size]);
    if (int_list_assign(&lol->items[lol->size], values, count) != 0) {
        return -1;
    }

    lol->size = new_size;
    return 0;
}

void list_of_lists_free(ListOfLists *lol)
{
    if (lol == NULL) {
        return;
    }
    if (lol->items != NULL) {
        for (size_t i = 0; i < lol->size; i++) {
            int_list_free(&lol->items[i]);
        }
        free(lol->items);
    }
    lol->items = NULL;
    lol->size = 0;
}

size_t remove_empty_lists(ListOfLists *lol)
{
    size_t write_index;
    size_t removed;

    if (lol == NULL) {
        return 0;
    }
    if (lol->size > 0 && lol->items == NULL) {
        return 0;
    }

    write_index = 0;
    for (size_t read_index = 0; read_index < lol->size; read_index++) {
        if (lol->items[read_index].size == 0) {
            int_list_free(&lol->items[read_index]);
        } else {
            if (write_index != read_index) {
                lol->items[write_index] = lol->items[read_index];
                lol->items[read_index].data = NULL;
                lol->items[read_index].size = 0;
            }
            write_index++;
        }
    }

    removed = lol->size - write_index;
    lol->size = write_index;
    return removed;
}

void list_of_lists_print(const ListOfLists *lol)
{
    if (lol == NULL) {
        return;
    }
    printf("[");
    for (size_t i = 0; i < lol->size; i++) {
        printf("[");
        for (size_t j = 0; j < lol->items[i].size; j++) {
            printf("%d", lol->items[i].data[j]);
            if (j + 1 < lol->items[i].size) {
                printf(", ");
            }
        }
        printf("]");
        if (i + 1 < lol->size) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    ListOfLists lol;
    int a[] = {1, 2, 3};
    int b[] = {4, 5};
    int c[] = {6};
    size_t removed;

    list_of_lists_init(&lol);

    if (list_of_lists_push(&lol, a, sizeof(a) / sizeof(*a)) != 0 ||
        list_of_lists_push(&lol, NULL, 0) != 0 ||
        list_of_lists_push(&lol, b, sizeof(b) / sizeof(*b)) != 0 ||
        list_of_lists_push(&lol, NULL, 0) != 0 ||
        list_of_lists_push(&lol, c, sizeof(c) / sizeof(*c)) != 0) {
        fprintf(stderr, "Failed to build list of lists\n");
        list_of_lists_free(&lol);
        return EXIT_FAILURE;
    }

    printf("Before:  ");
    list_of_lists_print(&lol);

    removed = remove_empty_lists(&lol);

    printf("After:   ");
    list_of_lists_print(&lol);
    printf("Removed: %zu\n", removed);

    list_of_lists_free(&lol);
    return EXIT_SUCCESS;
}