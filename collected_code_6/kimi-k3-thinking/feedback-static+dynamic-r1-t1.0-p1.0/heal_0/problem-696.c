#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
} IntList;

typedef struct {
    IntList *items;
    size_t count;
} ListOfLists;

typedef struct {
    IntList first;
    IntList second;
} ListPair;

typedef struct {
    ListPair *pairs;
    size_t count;
} ZippedLists;

static int copy_int_list(IntList *dst, const IntList *src)
{
    dst->data = NULL;
    dst->size = 0;

    if (src == NULL) {
        return 0;
    }
    if (src->size == 0) {
        return 1;
    }
    if (src->data == NULL || src->size > SIZE_MAX / sizeof(int)) {
        return 0;
    }

    dst->data = (int *)malloc(src->size * sizeof(int));
    if (dst->data == NULL) {
        return 0;
    }
    for (size_t i = 0; i < src->size; ++i) {
        dst->data[i] = src->data[i];
    }
    dst->size = src->size;
    return 1;
}

ZippedLists zip_lists_of_lists(const ListOfLists *lhs, const ListOfLists *rhs)
{
    ZippedLists result;
    result.pairs = NULL;
    result.count = 0;

    if (lhs == NULL || rhs == NULL) {
        return result;
    }

    size_t count = lhs->count < rhs->count ? lhs->count : rhs->count;
    if (count == 0) {
        return result;
    }
    if (lhs->items == NULL || rhs->items == NULL) {
        return result;
    }
    if (count > SIZE_MAX / sizeof(ListPair)) {
        return result;
    }

    result.pairs = (ListPair *)calloc(count, sizeof(ListPair));
    if (result.pairs == NULL) {
        return result;
    }

    size_t done = 0;
    for (size_t i = 0; i < count; ++i) {
        if (!copy_int_list(&result.pairs[i].first, &lhs->items[i]) ||
            !copy_int_list(&result.pairs[i].second, &rhs->items[i])) {
            break;
        }
        ++done;
    }

    if (done != count) {
        for (size_t i = 0; i < count; ++i) {
            free(result.pairs[i].first.data);
            free(result.pairs[i].second.data);
        }
        free(result.pairs);
        result.pairs = NULL;
        return result;
    }

    result.count = count;
    return result;
}

void free_zipped_lists(ZippedLists *zipped)
{
    if (zipped == NULL) {
        return;
    }
    for (size_t i = 0; i < zipped->count; ++i) {
        free(zipped->pairs[i].first.data);
        free(zipped->pairs[i].second.data);
    }
    free(zipped->pairs);
    zipped->pairs = NULL;
    zipped->count = 0;
}

static int init_list_of_lists(ListOfLists *lol,
                              const int *const *rows,
                              const size_t *row_sizes,
                              size_t count)
{
    lol->items = NULL;
    lol->count = 0;

    if (count == 0) {
        return 1;
    }
    if (rows == NULL || row_sizes == NULL || count > SIZE_MAX / sizeof(IntList)) {
        return 0;
    }

    lol->items = (IntList *)calloc(count, sizeof(IntList));
    if (lol->items == NULL) {
        return 0;
    }
    lol->count = count;

    for (size_t i = 0; i < count; ++i) {
        if (row_sizes[i] == 0) {
            continue;
        }
        if (rows[i] == NULL || row_sizes[i] > SIZE_MAX / sizeof(int)) {
            return 0;
        }
        lol->items[i].data = (int *)malloc(row_sizes[i] * sizeof(int));
        if (lol->items[i].data == NULL) {
            return 0;
        }
        for (size_t j = 0; j < row_sizes[i]; ++j) {
            lol->items[i].data[j] = rows[i][j];
        }
        lol->items[i].size = row_sizes[i];
    }
    return 1;
}

void free_list_of_lists(ListOfLists *lol)
{
    if (lol == NULL) {
        return;
    }
    for (size_t i = 0; i < lol->count; ++i) {
        free(lol->items[i].data);
    }
    free(lol->items);
    lol->items = NULL;
    lol->count = 0;
}

static void print_int_list(const IntList *list)
{
    printf("[");
    if (list != NULL) {
        for (size_t i = 0; i < list->size; ++i) {
            printf("%s%d", i == 0 ? "" : ", ", list->data[i]);
        }
    }
    printf("]");
}

static void print_zipped_lists(const ZippedLists *zipped)
{
    if (zipped == NULL) {
        return;
    }
    for (size_t i = 0; i < zipped->count; ++i) {
        printf("Pair %zu: (", i);
        print_int_list(&zipped->pairs[i].first);
        printf(", ");
        print_int_list(&zipped->pairs[i].second);
        printf(")\n");
    }
}

int main(void)
{
    int a_row0[] = {1, 2, 3};
    int a_row1[] = {4, 5};
    int b_row0[] = {10, 20};
    int b_row1[] = {30, 40, 50};

    const int *a_rows[] = {a_row0, a_row1};
    const int *b_rows[] = {b_row0, b_row1};
    const size_t a_sizes[] = {sizeof a_row0 / sizeof a_row0[0],
                              sizeof a_row1 / sizeof a_row1[0]};
    const size_t b_sizes[] = {sizeof b_row0 / sizeof b_row0[0],
                              sizeof b_row1 / sizeof b_row1[0]};
    const size_t row_count = 2;

    ListOfLists a;
    ListOfLists b;
    int status = EXIT_SUCCESS;

    if (!init_list_of_lists(&a, a_rows, a_sizes, row_count)) {
        free_list_of_lists(&a);
        fprintf(stderr, "failed to build first list of lists\n");
        return EXIT_FAILURE;
    }
    if (!init_list_of_lists(&b, b_rows, b_sizes, row_count)) {
        free_list_of_lists(&a);
        free_list_of_lists(&b);
        fprintf(stderr, "failed to build second list of lists\n");
        return EXIT_FAILURE;
    }

    ZippedLists zipped = zip_lists_of_lists(&a, &b);
    if (zipped.pairs == NULL || zipped.count != row_count) {
        fprintf(stderr, "failed to zip lists\n");
        status = EXIT_FAILURE;
    } else {
        print_zipped_lists(&zipped);
    }

    free_zipped_lists(&zipped);
    free_list_of_lists(&a);
    free_list_of_lists(&b);

    return status;
}