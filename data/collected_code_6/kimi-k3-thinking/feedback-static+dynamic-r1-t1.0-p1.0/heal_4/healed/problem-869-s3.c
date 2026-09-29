#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} IntList;

typedef struct {
    IntList *lists;
    size_t count;
} ListOfLists;

static int init_sublist(IntList *list, const int *src, size_t n)
{
    if (list == NULL) {
        return -1;
    }
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
    if (n == 0) {
        return 0;
    }
    if (src == NULL) {
        return -1;
    }
    if (n > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    size_t bytes = n * sizeof(int);
    int *buffer = (int *)malloc(bytes);
    if (buffer == NULL) {
        return -1;
    }
    for (size_t i = 0; i < n; i++) {
        buffer[i] = src[i];
    }
    list->data = buffer;
    list->size = n;
    list->capacity = n;
    return 0;
}

static int sublist_within_range(const IntList *list, int min_val, int max_val)
{
    if (list == NULL || (list->data == NULL && list->size > 0)) {
        return 0;
    }
    for (size_t i = 0; i < list->size; i++) {
        if (list->data[i] < min_val || list->data[i] > max_val) {
            return 0;
        }
    }
    return 1;
}

int remove_sublists_outside_range(ListOfLists *ll, int min_val, int max_val)
{
    if (ll == NULL || (ll->lists == NULL && ll->count > 0) || min_val > max_val) {
        return -1;
    }
    size_t keep = 0;
    for (size_t i = 0; i < ll->count; i++) {
        if (sublist_within_range(&ll->lists[i], min_val, max_val)) {
            if (keep != i) {
                ll->lists[keep] = ll->lists[i];
                ll->lists[i].data = NULL;
                ll->lists[i].size = 0;
                ll->lists[i].capacity = 0;
            }
            keep++;
        } else {
            free(ll->lists[i].data);
            ll->lists[i].data = NULL;
            ll->lists[i].size = 0;
            ll->lists[i].capacity = 0;
        }
    }
    ll->count = keep;
    return 0;
}

void free_list_of_lists(ListOfLists *ll)
{
    if (ll == NULL) {
        return;
    }
    if (ll->lists != NULL) {
        for (size_t i = 0; i < ll->count; i++) {
            free(ll->lists[i].data);
            ll->lists[i].data = NULL;
            ll->lists[i].size = 0;
            ll->lists[i].capacity = 0;
        }
        free(ll->lists);
        ll->lists = NULL;
    }
    ll->count = 0;
}

static void print_lists(const ListOfLists *ll)
{
    if (ll == NULL) {
        return;
    }
    for (size_t i = 0; i < ll->count; i++) {
        if (ll->lists[i].data == NULL && ll->lists[i].size > 0) {
            continue;
        }
        printf("[");
        for (size_t j = 0; j < ll->lists[i].size; j++) {
            printf("%d", ll->lists[i].data[j]);
            if (j + 1 < ll->lists[i].size) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

int main(void)
{
    static const int a[] = {1, 2, 3};
    static const int b[] = {0, 4};
    static const int c[] = {5, 6, 7};
    static const int d[] = {8, 100};
    static const int e[] = {13, 14, 15};
    ListOfLists ll;

    ll.lists = (IntList *)malloc(5 * sizeof(IntList));
    if (ll.lists == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    ll.count = 5;
    for (size_t i = 0; i < ll.count; i++) {
        ll.lists[i].data = NULL;
        ll.lists[i].size = 0;
        ll.lists[i].capacity = 0;
    }

    if (init_sublist(&ll.lists[0], a, sizeof(a) / sizeof(a[0])) != 0 ||
        init_sublist(&ll.lists[1], b, sizeof(b) / sizeof(b[0])) != 0 ||
        init_sublist(&ll.lists[2], c, sizeof(c) / sizeof(c[0])) != 0 ||
        init_sublist(&ll.lists[3], d, sizeof(d) / sizeof(d[0])) != 0 ||
        init_sublist(&ll.lists[4], e, sizeof(e) / sizeof(e[0])) != 0) {
        fprintf(stderr, "Initialization failed\n");
        free_list_of_lists(&ll);
        return EXIT_FAILURE;
    }

    printf("Original list of lists:\n");
    print_lists(&ll);

    if (remove_sublists_outside_range(&ll, 0, 15) != 0) {
        fprintf(stderr, "Removal failed\n");
        free_list_of_lists(&ll);
        return EXIT_FAILURE;
    }

    printf("After removing sublists outside range [0, 15]:\n");
    print_lists(&ll);

    free_list_of_lists(&ll);
    return EXIT_SUCCESS;
}