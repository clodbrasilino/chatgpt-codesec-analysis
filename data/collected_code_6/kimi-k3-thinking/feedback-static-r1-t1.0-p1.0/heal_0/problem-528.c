#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} IntList;

const IntList *find_min_length_list(const IntList *lists, size_t count)
{
    size_t i;
    size_t min_index;

    if (lists == NULL || count == 0U) {
        return NULL;
    }

    min_index = 0U;
    for (i = 1U; i < count; i++) {
        if (lists[i].length < lists[min_index].length) {
            min_index = i;
        }
    }

    return &lists[min_index];
}

static IntList create_list(const int *values, size_t length)
{
    IntList list;
    size_t i;

    list.data = NULL;
    list.length = 0U;

    if (values != NULL && length > 0U) {
        list.data = malloc(length * sizeof(*list.data));
        if (list.data != NULL) {
            for (i = 0U; i < length; i++) {
                list.data[i] = values[i];
            }
            list.length = length;
        }
    }

    return list;
}

static void destroy_list(IntList *list)
{
    if (list != NULL) {
        free(list->data);
        list->data = NULL;
        list->length = 0U;
    }
}

int main(void)
{
    int values0[] = {1, 2, 3, 4};
    int values1[] = {5, 6};
    int values2[] = {7, 8, 9};
    int values3[] = {10};

    IntList lists[4];
    const size_t count = sizeof(lists) / sizeof(lists[0]);
    const IntList *min_list;
    size_t i;
    int status = EXIT_SUCCESS;

    lists[0] = create_list(values0, sizeof(values0) / sizeof(values0[0]));
    lists[1] = create_list(values1, sizeof(values1) / sizeof(values1[0]));
    lists[2] = create_list(values2, sizeof(values2) / sizeof(values2[0]));
    lists[3] = create_list(values3, sizeof(values3) / sizeof(values3[0]));

    for (i = 0U; i < count; i++) {
        if (lists[i].data == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            status = EXIT_FAILURE;
            break;
        }
    }

    if (status == EXIT_SUCCESS) {
        min_list = find_min_length_list(lists, count);
        if (min_list != NULL) {
            printf("List with minimum length (length %zu):", min_list->length);
            for (i = 0U; i < min_list->length; i++) {
                printf(" %d", min_list->data[i]);
            }
            printf("\n");
        } else {
            printf("No lists available.\n");
        }
    }

    for (i = 0U; i < count; i++) {
        destroy_list(&lists[i]);
    }

    return status;
}