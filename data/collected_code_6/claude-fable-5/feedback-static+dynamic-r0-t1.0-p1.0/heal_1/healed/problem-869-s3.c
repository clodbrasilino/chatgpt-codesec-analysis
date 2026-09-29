#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *items;
    size_t length;
} IntList;

typedef struct {
    IntList *lists;
    size_t count;
} ListOfLists;

static int sublist_in_range(const IntList *list, int low, int high)
{
    if (list == NULL || list->items == NULL || list->length == 0U) {
        return 0;
    }

    for (size_t i = 0U; i < list->length; i++) {
        if ((list->items[i] < low) || (list->items[i] > high)) {
            return 0;
        }
    }

    return 1;
}

static int remove_sublists_outside_range(ListOfLists *container, int low, int high)
{
    size_t write_index;

    if (container == NULL) {
        return -1;
    }

    write_index = 0U;

    for (size_t read_index = 0U; read_index < container->count; read_index++) {
        if (sublist_in_range(&container->lists[read_index], low, high) == 1) {
            container->lists[write_index] = container->lists[read_index];
            write_index++;
        } else {
            free(container->lists[read_index].items);
            container->lists[read_index].items = NULL;
            container->lists[read_index].length = 0U;
        }
    }

    container->count = write_index;
    return 0;
}

static int init_sublist(IntList *list, const int *values, size_t length)
{
    if ((list == NULL) || (values == NULL) || (length == 0U)) {
        return -1;
    }

    if (length > (SIZE_MAX / sizeof(int))) {
        return -1;
    }

    list->items = (int *)malloc(length * sizeof(int));
    if (list->items == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < length; i++) {
        list->items[i] = values[i];
    }

    list->length = length;
    return 0;
}

static void free_container(ListOfLists *container)
{
    if (container == NULL) {
        return;
    }

    if (container->lists != NULL) {
        for (size_t i = 0U; i < container->count; i++) {
            free(container->lists[i].items);
            container->lists[i].items = NULL;
        }
        free(container->lists);
        container->lists = NULL;
    }

    container->count = 0U;
}

static void print_container(const ListOfLists *container)
{
    if (container == NULL) {
        return;
    }

    printf("[");
    for (size_t i = 0U; i < container->count; i++) {
        printf("[");
        for (size_t j = 0U; j < container->lists[i].length; j++) {
            printf("%d", container->lists[i].items[j]);
            if (j + 1U < container->lists[i].length) {
                printf(", ");
            }
        }
        printf("]");
        if (i + 1U < container->count) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    ListOfLists container;
    const int values1[] = {2, 4, 6};
    const int values2[] = {1, 15, 3};
    const int values3[] = {5, 7, 9};
    const int values4[] = {0, 8};
    int status;

    container.count = 4U;
    container.lists = (IntList *)malloc(container.count * sizeof(IntList));
    if (container.lists == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < container.count; i++) {
        container.lists[i].items = NULL;
        container.lists[i].length = 0U;
    }

    status = init_sublist(&container.lists[0], values1, sizeof(values1) / sizeof(values1[0]));
    if (status == 0) {
        status = init_sublist(&container.lists[1], values2, sizeof(values2) / sizeof(values2[0]));
    }
    if (status == 0) {
        status = init_sublist(&container.lists[2], values3, sizeof(values3) / sizeof(values3[0]));
    }
    if (status == 0) {
        status = init_sublist(&container.lists[3], values4, sizeof(values4) / sizeof(values4[0]));
    }

    if (status != 0) {
        fprintf(stderr, "Failed to initialize sublists\n");
        free_container(&container);
        return EXIT_FAILURE;
    }

    printf("Original list of lists:\n");
    print_container(&container);

    status = remove_sublists_outside_range(&container, 1, 10);
    if (status != 0) {
        fprintf(stderr, "Failed to filter sublists\n");
        free_container(&container);
        return EXIT_FAILURE;
    }

    printf("After removing sublists outside range [1, 10]:\n");
    print_container(&container);

    free_container(&container);
    return EXIT_SUCCESS;
}