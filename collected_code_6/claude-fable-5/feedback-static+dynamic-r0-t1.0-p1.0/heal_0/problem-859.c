#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t count;
} Sublist;

typedef struct {
    Sublist *lists;
    size_t total;
} SublistSet;

static void freeSublistSet(SublistSet *set)
{
    size_t i;

    if (set == NULL) {
        return;
    }
    if (set->lists != NULL) {
        for (i = 0; i < set->total; i++) {
            free(set->lists[i].items);
        }
        free(set->lists);
    }
    free(set);
}

static SublistSet *generateSublists(const int *list, size_t n)
{
    SublistSet *set;
    size_t total;
    size_t mask;
    size_t bit;
    size_t count;
    size_t idx;

    if (list == NULL && n > 0) {
        return NULL;
    }
    if (n >= (sizeof(size_t) * 8U) - 1U) {
        return NULL;
    }

    total = (size_t)1 << n;

    set = malloc(sizeof(SublistSet));
    if (set == NULL) {
        return NULL;
    }

    set->lists = calloc(total, sizeof(Sublist));
    if (set->lists == NULL) {
        free(set);
        return NULL;
    }
    set->total = total;

    for (mask = 0; mask < total; mask++) {
        count = 0;
        for (bit = 0; bit < n; bit++) {
            if ((mask & ((size_t)1 << bit)) != 0U) {
                count++;
            }
        }
        set->lists[mask].count = count;
        if (count > 0) {
            set->lists[mask].items = malloc(count * sizeof(int));
            if (set->lists[mask].items == NULL) {
                freeSublistSet(set);
                return NULL;
            }
            idx = 0;
            for (bit = 0; bit < n; bit++) {
                if ((mask & ((size_t)1 << bit)) != 0U) {
                    set->lists[mask].items[idx] = list[bit];
                    idx++;
                }
            }
        } else {
            set->lists[mask].items = NULL;
        }
    }

    return set;
}

static void printSublistSet(const SublistSet *set)
{
    size_t i;
    size_t j;

    if (set == NULL) {
        return;
    }

    for (i = 0; i < set->total; i++) {
        printf("[");
        for (j = 0; j < set->lists[i].count; j++) {
            if (j > 0) {
                printf(", ");
            }
            printf("%d", set->lists[i].items[j]);
        }
        printf("]\n");
    }
}

int main(void)
{
    int list[] = {1, 2, 3, 4};
    size_t n = sizeof(list) / sizeof(list[0]);
    SublistSet *set;

    set = generateSublists(list, n);
    if (set == NULL) {
        fprintf(stderr, "Failed to generate sublists\n");
        return EXIT_FAILURE;
    }

    printSublistSet(set);
    freeSublistSet(set);

    return EXIT_SUCCESS;
}