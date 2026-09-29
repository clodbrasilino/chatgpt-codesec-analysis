#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
} IntList;

typedef struct {
    IntList *lists;
    size_t size;
} ListOfLists;

typedef struct {
    IntList *first;
    IntList *second;
} IntListPair;

typedef struct {
    IntListPair *pairs;
    size_t size;
} ZippedLists;

ZippedLists *zip_lists_of_lists(const ListOfLists *first, const ListOfLists *second);
void free_zipped_lists(ZippedLists *zipped);

static void print_int_list(const IntList *list)
{
    printf("[");
    if (list != NULL) {
        for (size_t i = 0; i < list->size; i++) {
            printf("%d", list->data[i]);
            if (i + 1 < list->size) {
                printf(", ");
            }
        }
    }
    printf("]");
}

static void print_list_of_lists(const ListOfLists *lol)
{
    printf("[");
    if (lol != NULL) {
        for (size_t i = 0; i < lol->size; i++) {
            print_int_list(&lol->lists[i]);
            if (i + 1 < lol->size) {
                printf(", ");
            }
        }
    }
    printf("]\n");
}

static void print_zipped_lists(const ZippedLists *zipped)
{
    printf("[");
    if (zipped != NULL) {
        for (size_t i = 0; i < zipped->size; i++) {
            printf("(");
            print_int_list(zipped->pairs[i].first);
            printf(", ");
            print_int_list(zipped->pairs[i].second);
            printf(")");
            if (i + 1 < zipped->size) {
                printf(", ");
            }
        }
    }
    printf("]\n");
}

static IntList *copy_int_list(const IntList *src)
{
    IntList *copy;

    if (src == NULL) {
        return NULL;
    }
    if (src->size > 0 && src->data == NULL) {
        return NULL;
    }
    if (src->size > SIZE_MAX / sizeof *src->data) {
        return NULL;
    }
    copy = malloc(sizeof *copy);
    if (copy == NULL) {
        return NULL;
    }
    copy->size = src->size;
    copy->data = NULL;
    if (src->size > 0) {
        copy->data = malloc(src->size * sizeof *copy->data);
        if (copy->data == NULL) {
            free(copy);
            return NULL;
        }
        for (size_t i = 0; i < src->size; i++) {
            copy->data[i] = src->data[i];
        }
    }
    return copy;
}

static ListOfLists *create_list_of_lists(size_t count)
{
    ListOfLists *lol;

    if (count > SIZE_MAX / sizeof *lol->lists) {
        return NULL;
    }
    lol = malloc(sizeof *lol);
    if (lol == NULL) {
        return NULL;
    }
    lol->size = count;
    lol->lists = NULL;
    if (count > 0) {
        lol->lists = calloc(count, sizeof *lol->lists);
        if (lol->lists == NULL) {
            free(lol);
            return NULL;
        }
    }
    return lol;
}

static int set_int_list(ListOfLists *lol, size_t index, const int *values, size_t size)
{
    if (lol == NULL || index >= lol->size) {
        return -1;
    }
    if (size > 0 && values == NULL) {
        return -1;
    }
    if (size > SIZE_MAX / sizeof *values) {
        return -1;
    }
    lol->lists[index].size = 0;
    lol->lists[index].data = NULL;
    if (size > 0) {
        lol->lists[index].data = malloc(size * sizeof *lol->lists[index].data);
        if (lol->lists[index].data == NULL) {
            return -1;
        }
        for (size_t i = 0; i < size; i++) {
            lol->lists[index].data[i] = values[i];
        }
        lol->lists[index].size = size;
    }
    return 0;
}

static void free_list_of_lists(ListOfLists *lol)
{
    if (lol == NULL) {
        return;
    }
    for (size_t i = 0; i < lol->size; i++) {
        free(lol->lists[i].data);
    }
    free(lol->lists);
    free(lol);
}

void free_zipped_lists(ZippedLists *zipped)
{
    if (zipped == NULL) {
        return;
    }
    for (size_t i = 0; i < zipped->size; i++) {
        if (zipped->pairs[i].first != NULL) {
            free(zipped->pairs[i].first->data);
            free(zipped->pairs[i].first);
        }
        if (zipped->pairs[i].second != NULL) {
            free(zipped->pairs[i].second->data);
            free(zipped->pairs[i].second);
        }
    }
    free(zipped->pairs);
    free(zipped);
}

ZippedLists *zip_lists_of_lists(const ListOfLists *first, const ListOfLists *second)
{
    ZippedLists *result;
    size_t count;

    if (first == NULL || second == NULL) {
        return NULL;
    }
    if (first->size > 0 && first->lists == NULL) {
        return NULL;
    }
    if (second->size > 0 && second->lists == NULL) {
        return NULL;
    }
    count = first->size < second->size ? first->size : second->size;
    if (count > SIZE_MAX / sizeof *result->pairs) {
        return NULL;
    }
    result = malloc(sizeof *result);
    if (result == NULL) {
        return NULL;
    }
    result->size = 0;
    result->pairs = NULL;
    if (count == 0) {
        return result;
    }
    result->pairs = calloc(count, sizeof *result->pairs);
    if (result->pairs == NULL) {
        free(result);
        return NULL;
    }
    result->size = count;
    for (size_t i = 0; i < count; i++) {
        result->pairs[i].first = copy_int_list(&first->lists[i]);
        result->pairs[i].second = copy_int_list(&second->lists[i]);
        if (result->pairs[i].first == NULL || result->pairs[i].second == NULL) {
            free_zipped_lists(result);
            return NULL;
        }
    }
    return result;
}

int main(void)
{
    int status = EXIT_FAILURE;
    ListOfLists *first = NULL;
    ListOfLists *second = NULL;
    ZippedLists *zipped = NULL;

    const int a_values_0[] = {1, 2, 3};
    const int a_values_1[] = {4, 5};
    const int b_values_0[] = {10, 20};
    const int b_values_1[] = {30, 40, 50};
    const int b_values_2[] = {60, 70};

    first = create_list_of_lists(2);
    second = create_list_of_lists(3);
    if (first == NULL || second == NULL) {
        fprintf(stderr, "failed to create lists\n");
        goto cleanup;
    }
    if (set_int_list(first, 0, a_values_0, sizeof a_values_0 / sizeof *a_values_0) != 0 ||
        set_int_list(first, 1, a_values_1, sizeof a_values_1 / sizeof *a_values_1) != 0 ||
        set_int_list(second, 0, b_values_0, sizeof b_values_0 / sizeof *b_values_0) != 0 ||
        set_int_list(second, 1, b_values_1, sizeof b_values_1 / sizeof *b_values_1) != 0 ||
        set_int_list(second, 2, b_values_2, sizeof b_values_2 / sizeof *b_values_2) != 0) {
        fprintf(stderr, "failed to initialize lists\n");
        goto cleanup;
    }

    zipped = zip_lists_of_lists(first, second);
    if (zipped == NULL) {
        fprintf(stderr, "failed to zip lists\n");
        goto cleanup;
    }

    printf("First:  ");
    print_list_of_lists(first);
    printf("Second: ");
    print_list_of_lists(second);
    printf("Zipped: ");
    print_zipped_lists(zipped);

    status = EXIT_SUCCESS;

cleanup:
    free_zipped_lists(zipped);
    free_list_of_lists(second);
    free_list_of_lists(first);
    return status;
}