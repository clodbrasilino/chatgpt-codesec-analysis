#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} IntList;

typedef void (*MapFunc)(int);

static void print_element(int value)
{
    printf("%d ", value);
}

static void map(const IntList *list, MapFunc func)
{
    size_t i;

    if (list == NULL || list->data == NULL || func == NULL) {
        return;
    }

    for (i = 0; i < list->size; i++) {
        func(list->data[i]);
    }
}

static void print_list_n_times(const IntList *list, size_t n)
{
    size_t i;

    if (list == NULL || list->data == NULL) {
        return;
    }

    for (i = 0; i < n; i++) {
        map(list, print_element);
        printf("\n");
    }
}

static int init_list(IntList *list, const int *values, size_t size)
{
    size_t i;

    if (list == NULL || (values == NULL && size > 0)) {
        return -1;
    }

    list->data = NULL;
    list->size = 0;

    if (size == 0) {
        return 0;
    }

    list->data = (int *)malloc(size * sizeof(*list->data));
    if (list->data == NULL) {
        return -1;
    }

    for (i = 0; i < size; i++) {
        list->data[i] = values[i];
    }

    list->size = size;
    return 0;
}

static void free_list(IntList *list)
{
    if (list == NULL) {
        return;
    }

    free(list->data);
    list->data = NULL;
    list->size = 0;
}

int main(void)
{
    int values[] = {1, 2, 3, 4, 5};
    IntList list;
    size_t n = 3;

    if (init_list(&list, values, sizeof(values) / sizeof(values[0])) != 0) {
        fprintf(stderr, "Failed to initialize list\n");
        return EXIT_FAILURE;
    }

    print_list_n_times(&list, n);
    free_list(&list);

    return EXIT_SUCCESS;
}