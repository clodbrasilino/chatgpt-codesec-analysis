#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
} IntList;

typedef struct {
    IntList *lists;
    size_t size;
} ListOfLists;

typedef struct {
    IntList first;
    IntList second;
} ZippedPair;

typedef struct {
    ZippedPair *pairs;
    size_t size;
} ZippedListOfLists;

int init_int_list(IntList *list, const int *data, size_t size) {
    if (!list) {
        return -1;
    }
    if (size > (size_t)-1 / sizeof(int)) {
        return -1;
    }
    list->size = size;
    if (size == 0) {
        list->data = NULL;
        return 0;
    }
    list->data = (int *)malloc(size * sizeof(int));
    if (!list->data) {
        list->size = 0;
        return -1;
    }
    if (data) {
        memcpy(list->data, data, size * sizeof(int));
    }
    return 0;
}

void free_int_list(IntList *list) {
    if (list && list->data) {
        free(list->data);
        list->data = NULL;
        list->size = 0;
    }
}

int copy_int_list(const IntList *src, IntList *dest) {
    if (!src || !dest) {
        return -1;
    }
    return init_int_list(dest, src->data, src->size);
}

int init_list_of_lists(ListOfLists *lol, size_t size) {
    size_t i;
    if (!lol) {
        return -1;
    }
    if (size > (size_t)-1 / sizeof(IntList)) {
        return -1;
    }
    lol->size = size;
    if (size == 0) {
        lol->lists = NULL;
        return 0;
    }
    lol->lists = (IntList *)malloc(size * sizeof(IntList));
    if (!lol->lists) {
        lol->size = 0;
        return -1;
    }
    for (i = 0; i < size; ++i) {
        lol->lists[i].data = NULL;
        lol->lists[i].size = 0;
    }
    return 0;
}

void free_list_of_lists(ListOfLists *lol) {
    size_t i;
    if (lol) {
        if (lol->lists) {
            for (i = 0; i < lol->size; ++i) {
                free_int_list(&lol->lists[i]);
            }
            free(lol->lists);
            lol->lists = NULL;
        }
        lol->size = 0;
    }
}

void free_zipped_list(ZippedListOfLists *zl) {
    size_t i;
    if (zl) {
        if (zl->pairs) {
            for (i = 0; i < zl->size; ++i) {
                free_int_list(&zl->pairs[i].first);
                free_int_list(&zl->pairs[i].second);
            }
            free(zl->pairs);
            zl->pairs = NULL;
        }
        zl->size = 0;
    }
}

int zip_lists_of_lists(const ListOfLists *a, const ListOfLists *b, ZippedListOfLists *out) {
    size_t min_size;
    size_t i;

    if (!a || !b || !out) {
        return -1;
    }

    min_size = (a->size < b->size) ? a->size : b->size;

    if (min_size > (size_t)-1 / sizeof(ZippedPair)) {
        return -1;
    }

    out->size = min_size;

    if (min_size == 0) {
        out->pairs = NULL;
        return 0;
    }

    out->pairs = (ZippedPair *)malloc(min_size * sizeof(ZippedPair));
    if (!out->pairs) {
        out->size = 0;
        return -1;
    }

    for (i = 0; i < min_size; ++i) {
        out->pairs[i].first.data = NULL;
        out->pairs[i].first.size = 0;
        out->pairs[i].second.data = NULL;
        out->pairs[i].second.size = 0;
    }

    for (i = 0; i < min_size; ++i) {
        if (copy_int_list(&a->lists[i], &out->pairs[i].first) != 0) {
            free_zipped_list(out);
            return -1;
        }
        if (copy_int_list(&b->lists[i], &out->pairs[i].second) != 0) {
            free_zipped_list(out);
            return -1;
        }
    }
    return 0;
}

int main(void) {
    ListOfLists list_a;
    ListOfLists list_b;
    ZippedListOfLists zipped;
    int row1_a[] = {1, 2, 3};
    int row2_a[] = {4, 5};
    int row1_b[] = {6, 7};
    int row2_b[] = {8, 9, 10, 11};
    size_t i;
    size_t j;

    list_a.lists = NULL;
    list_a.size = 0;
    list_b.lists = NULL;
    list_b.size = 0;
    zipped.pairs = NULL;
    zipped.size = 0;

    if (init_list_of_lists(&list_a, 2) != 0) {
        return EXIT_FAILURE;
    }

    if (init_int_list(&list_a.lists[0], row1_a, 3) != 0 ||
        init_int_list(&list_a.lists[1], row2_a, 2) != 0) {
        free_list_of_lists(&list_a);
        return EXIT_FAILURE;
    }

    if (init_list_of_lists(&list_b, 2) != 0) {
        free_list_of_lists(&list_a);
        return EXIT_FAILURE;
    }

    if (init_int_list(&list_b.lists[0], row1_b, 2) != 0 ||
        init_int_list(&list_b.lists[1], row2_b, 4) != 0) {
        free_list_of_lists(&list_a);
        free_list_of_lists(&list_b);
        return EXIT_FAILURE;
    }

    if (zip_lists_of_lists(&list_a, &list_b, &zipped) != 0) {
        free_list_of_lists(&list_a);
        free_list_of_lists(&list_b);
        return EXIT_FAILURE;
    }

    for (i = 0; i < zipped.size; ++i) {
        printf("Pair %zu:\n  First: ", i);
        for (j = 0; j < zipped.pairs[i].first.size; ++j) {
            printf("%d ", zipped.pairs[i].first.data[j]);
        }
        printf("\n  Second: ");
        for (j = 0; j < zipped.pairs[i].second.size; ++j) {
            printf("%d ", zipped.pairs[i].second.data[j]);
        }
        printf("\n");
    }

    free_zipped_list(&zipped);
    free_list_of_lists(&list_b);
    free_list_of_lists(&list_a);

    return EXIT_SUCCESS;
}