#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *elements;
    size_t count;
} IntList;

typedef struct {
    IntList *lists;
    size_t count;
} ListOfLists;

typedef struct {
    IntList first;
    IntList second;
} IntListPair;

typedef struct {
    IntListPair *pairs;
    size_t count;
} ZippedListOfLists;

IntList deep_copy_intlist(IntList src) {
    IntList dst;
    dst.count = 0;
    dst.elements = NULL;
    if (src.count > 0) {
        if (src.elements == NULL) {
            return dst;
        }
        if (src.count > SIZE_MAX / sizeof(int)) {
            return dst;
        }
        size_t byte_count = src.count * sizeof(int);
        dst.elements = (int *)malloc(byte_count);
        if (dst.elements == NULL) {
            return dst;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dst.elements, src.elements, byte_count);
        dst.count = src.count;
    }
    return dst;
}

void free_intlist(IntList *list) {
    if (list != NULL) {
        free(list->elements);
        list->elements = NULL;
        list->count = 0;
    }
}

void free_list_of_lists(ListOfLists *lol) {
    if (lol != NULL) {
        if (lol->lists != NULL) {
            for (size_t i = 0; i < lol->count; ++i) {
                free_intlist(&lol->lists[i]);
            }
            free(lol->lists);
        }
        lol->lists = NULL;
        lol->count = 0;
    }
}

void free_zipped_list_of_lists(ZippedListOfLists *zlol) {
    if (zlol != NULL) {
        if (zlol->pairs != NULL) {
            for (size_t i = 0; i < zlol->count; ++i) {
                free_intlist(&zlol->pairs[i].first);
                free_intlist(&zlol->pairs[i].second);
            }
            free(zlol->pairs);
        }
        zlol->pairs = NULL;
        zlol->count = 0;
    }
}

ZippedListOfLists zip_lists_of_lists(const ListOfLists *a, const ListOfLists *b) {
    ZippedListOfLists result;
    result.pairs = NULL;
    result.count = 0;

    if (a == NULL || b == NULL) {
        return result;
    }

    if ((a->count > 0 && a->lists == NULL) || (b->count > 0 && b->lists == NULL)) {
        return result;
    }

    size_t min_count = a->count < b->count ? a->count : b->count;
    if (min_count == 0) {
        return result;
    }

    result.pairs = (IntListPair *)calloc(min_count, sizeof(IntListPair));
    if (result.pairs == NULL) {
        return result;
    }
    result.count = min_count;

    for (size_t i = 0; i < min_count; ++i) {
        result.pairs[i].first = deep_copy_intlist(a->lists[i]);
        if (a->lists[i].count > 0 && result.pairs[i].first.count == 0) {
            for (size_t j = 0; j < i; ++j) {
                free(result.pairs[j].first.elements);
                free(result.pairs[j].second.elements);
            }
            free(result.pairs);
            result.pairs = NULL;
            result.count = 0;
            return result;
        }

        result.pairs[i].second = deep_copy_intlist(b->lists[i]);
        if (b->lists[i].count > 0 && result.pairs[i].second.count == 0) {
            for (size_t j = 0; j < i; ++j) {
                free(result.pairs[j].first.elements);
                free(result.pairs[j].second.elements);
            }
            free(result.pairs[i].first.elements);
            free(result.pairs);
            result.pairs = NULL;
            result.count = 0;
            return result;
        }
    }

    return result;
}

int main(void) {
    ListOfLists a;
    a.count = 2;
    a.lists = (IntList *)calloc(2, sizeof(IntList));
    if (a.lists == NULL) return 1;

    a.lists[0].count = 2;
    a.lists[0].elements = (int *)malloc(2 * sizeof(int));
    if (a.lists[0].elements == NULL) { free_list_of_lists(&a); return 1; }
    a.lists[0].elements[0] = 1;
    a.lists[0].elements[1] = 2;

    a.lists[1].count = 1;
    a.lists[1].elements = (int *)malloc(1 * sizeof(int));
    if (a.lists[1].elements == NULL) { free_list_of_lists(&a); return 1; }
    a.lists[1].elements[0] = 3;

    ListOfLists b;
    b.count = 2;
    b.lists = (IntList *)calloc(2, sizeof(IntList));
    if (b.lists == NULL) { free_list_of_lists(&a); return 1; }

    b.lists[0].count = 2;
    b.lists[0].elements = (int *)malloc(2 * sizeof(int));
    if (b.lists[0].elements == NULL) { free_list_of_lists(&a); free_list_of_lists(&b); return 1; }
    b.lists[0].elements[0] = 4;
    b.lists[0].elements[1] = 5;

    b.lists[1].count = 1;
    b.lists[1].elements = (int *)malloc(1 * sizeof(int));
    if (b.lists[1].elements == NULL) { free_list_of_lists(&a); free_list_of_lists(&b); return 1; }
    b.lists[1].elements[0] = 6;

    ZippedListOfLists zipped = zip_lists_of_lists(&a, &b);

    for (size_t i = 0; i < zipped.count; ++i) {
        printf("Pair %zu:\n  First: ", i);
        for (size_t j = 0; j < zipped.pairs[i].first.count; ++j) {
            printf("%d ", zipped.pairs[i].first.elements[j]);
        }
        printf("\n  Second: ");
        for (size_t j = 0; j < zipped.pairs[i].second.count; ++j) {
            printf("%d ", zipped.pairs[i].second.elements[j]);
        }
        printf("\n");
    }

    free_list_of_lists(&a);
    free_list_of_lists(&b);
    free_zipped_list_of_lists(&zipped);

    return 0;
}