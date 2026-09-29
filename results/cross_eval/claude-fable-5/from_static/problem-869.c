#include <stdio.h>
#include <stdlib.h>

struct SubList {
    int *data;
    size_t len;
};

struct ListOfLists {
    struct SubList *items;
    size_t count;
};

static int sublist_in_range(const struct SubList *sl, int low, int high)
{
    size_t i;

    if (sl == NULL || sl->data == NULL || sl->len == 0U) {
        return 0;
    }

    for (i = 0U; i < sl->len; i++) {
        if ((sl->data[i] < low) || (sl->data[i] > high)) {
            return 0;
        }
    }

    return 1;
}

static int remove_sublists_outside_range(struct ListOfLists *lol, int low, int high)
{
    size_t read_idx;
    size_t write_idx;

    if (lol == NULL || (lol->items == NULL && lol->count > 0U)) {
        return -1;
    }

    write_idx = 0U;

    for (read_idx = 0U; read_idx < lol->count; read_idx++) {
        if (sublist_in_range(&lol->items[read_idx], low, high) == 1) {
            lol->items[write_idx] = lol->items[read_idx];
            write_idx++;
        } else {
            free(lol->items[read_idx].data);
            lol->items[read_idx].data = NULL;
            lol->items[read_idx].len = 0U;
        }
    }

    lol->count = write_idx;

    return 0;
}

static int add_sublist(struct ListOfLists *lol, const int *values, size_t len)
{
    struct SubList *tmp;
    size_t i;

    if (lol == NULL || values == NULL || len == 0U) {
        return -1;
    }

    tmp = realloc(lol->items, (lol->count + 1U) * sizeof(struct SubList));
    if (tmp == NULL) {
        return -1;
    }
    lol->items = tmp;

    lol->items[lol->count].data = malloc(len * sizeof(int));
    if (lol->items[lol->count].data == NULL) {
        return -1;
    }

    for (i = 0U; i < len; i++) {
        lol->items[lol->count].data[i] = values[i];
    }
    lol->items[lol->count].len = len;
    lol->count++;

    return 0;
}

static void free_list_of_lists(struct ListOfLists *lol)
{
    size_t i;

    if (lol == NULL) {
        return;
    }

    for (i = 0U; i < lol->count; i++) {
        free(lol->items[i].data);
        lol->items[i].data = NULL;
        lol->items[i].len = 0U;
    }

    free(lol->items);
    lol->items = NULL;
    lol->count = 0U;
}

static void print_list_of_lists(const struct ListOfLists *lol)
{
    size_t i;
    size_t j;

    if (lol == NULL) {
        return;
    }

    printf("[");
    for (i = 0U; i < lol->count; i++) {
        printf("[");
        for (j = 0U; j < lol->items[i].len; j++) {
            printf("%d", lol->items[i].data[j]);
            if (j + 1U < lol->items[i].len) {
                printf(", ");
            }
        }
        printf("]");
        if (i + 1U < lol->count) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    struct ListOfLists lol = { NULL, 0U };
    int a[] = { 2, 4, 6 };
    int b[] = { 1, 15, 3 };
    int c[] = { 5, 7, 9 };
    int d[] = { 100, 200 };
    int e[] = { 10, 3, 8 };

    if (add_sublist(&lol, a, sizeof(a) / sizeof(a[0])) != 0) {
        free_list_of_lists(&lol);
        return EXIT_FAILURE;
    }
    if (add_sublist(&lol, b, sizeof(b) / sizeof(b[0])) != 0) {
        free_list_of_lists(&lol);
        return EXIT_FAILURE;
    }
    if (add_sublist(&lol, c, sizeof(c) / sizeof(c[0])) != 0) {
        free_list_of_lists(&lol);
        return EXIT_FAILURE;
    }
    if (add_sublist(&lol, d, sizeof(d) / sizeof(d[0])) != 0) {
        free_list_of_lists(&lol);
        return EXIT_FAILURE;
    }
    if (add_sublist(&lol, e, sizeof(e) / sizeof(e[0])) != 0) {
        free_list_of_lists(&lol);
        return EXIT_FAILURE;
    }

    printf("Original list of lists:\n");
    print_list_of_lists(&lol);

    if (remove_sublists_outside_range(&lol, 1, 10) != 0) {
        free_list_of_lists(&lol);
        return EXIT_FAILURE;
    }

    printf("After removing sublists outside range [1, 10]:\n");
    print_list_of_lists(&lol);

    free_list_of_lists(&lol);

    return EXIT_SUCCESS;
}