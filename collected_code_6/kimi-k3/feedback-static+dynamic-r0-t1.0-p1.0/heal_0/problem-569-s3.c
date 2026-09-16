#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} StringList;

typedef struct {
    StringList *lists;
    size_t count;
} ListOfLists;

static int compare_strings(const void *a, const void *b)
{
    const char *sa = *(const char * const *)a;
    const char *sb = *(const char * const *)b;
    return strcmp(sa, sb);
}

static int sort_sublists(ListOfLists *container)
{
    size_t i;

    if (container == NULL) {
        return -1;
    }

    if (container->count > 0 && container->lists == NULL) {
        return -1;
    }

    for (i = 0; i < container->count; ++i) {
        StringList *sublist = &container->lists[i];

        if (sublist->count > 0 && sublist->items == NULL) {
            return -1;
        }

        if (sublist->count > 1) {
            qsort(sublist->items, sublist->count, sizeof(sublist->items[0]), compare_strings);
        }
    }

    return 0;
}

static void free_string_list(StringList *list)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    if (list->items != NULL) {
        for (i = 0; i < list->count; ++i) {
            free(list->items[i]);
            list->items[i] = NULL;
        }
        free(list->items);
        list->items = NULL;
    }

    list->count = 0;
}

static void free_list_of_lists(ListOfLists *container)
{
    size_t i;

    if (container == NULL) {
        return;
    }

    if (container->lists != NULL) {
        for (i = 0; i < container->count; ++i) {
            free_string_list(&container->lists[i]);
        }
        free(container->lists);
        container->lists = NULL;
    }

    container->count = 0;
}

static int init_string_list(StringList *list, const char *const *values, size_t count)
{
    size_t i;

    if (list == NULL || (count > 0 && values == NULL)) {
        return -1;
    }

    list->items = NULL;
    list->count = 0;

    if (count == 0) {
        return 0;
    }

    list->items = (char **)calloc(count, sizeof(list->items[0]));
    if (list->items == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (values[i] == NULL) {
            free_string_list(list);
            return -1;
        }

        list->items[i] = (char *)malloc(strlen(values[i]) + 1);
        if (list->items[i] == NULL) {
            free_string_list(list);
            return -1;
        }

        strcpy(list->items[i], values[i]);
    }

    list->count = count;
    return 0;
}

static int init_list_of_lists(ListOfLists *container, const char *const *const *values, const size_t *counts, size_t list_count)
{
    size_t i;

    if (container == NULL || (list_count > 0 && (values == NULL || counts == NULL))) {
        return -1;
    }

    container->lists = NULL;
    container->count = 0;

    if (list_count == 0) {
        return 0;
    }

    container->lists = (StringList *)calloc(list_count, sizeof(container->lists[0]));
    if (container->lists == NULL) {
        return -1;
    }

    for (i = 0; i < list_count; ++i) {
        if (init_string_list(&container->lists[i], values[i], counts[i]) != 0) {
            free_list_of_lists(container);
            return -1;
        }
    }

    container->count = list_count;
    return 0;
}

static void print_list_of_lists(const ListOfLists *container)
{
    size_t i;
    size_t j;

    if (container == NULL || (container->count > 0 && container->lists == NULL)) {
        return;
    }

    for (i = 0; i < container->count; ++i) {
        printf("[");
        for (j = 0; j < container->lists[i].count; ++j) {
            printf("\"%s\"%s", container->lists[i].items[j], (j + 1 < container->lists[i].count) ? ", " : "");
        }
        printf("]\n");
    }
}

int main(void)
{
    const char *sublist1[] = {"banana", "apple", "cherry"};
    const char *sublist2[] = {"zebra", "lion", "elephant", "ant"};
    const char *sublist3[] = {"red", "blue", "green", "yellow", "purple"};
    const char *sublist4[] = {"single"};
    const char **all_sublists[] = {sublist1, sublist2, sublist3, sublist4};
    const size_t counts[] = {
        sizeof(sublist1) / sizeof(sublist1[0]),
        sizeof(sublist2) / sizeof(sublist2[0]),
        sizeof(sublist3) / sizeof(sublist3[0]),
        sizeof(sublist4) / sizeof(sublist4[0])
    };
    const size_t list_count = sizeof(all_sublists) / sizeof(all_sublists[0]);
    ListOfLists container;
    int status = EXIT_FAILURE;

    if (init_list_of_lists(&container, all_sublists, counts, list_count) != 0) {
        fprintf(stderr, "Failed to initialize list of lists\n");
        return EXIT_FAILURE;
    }

    printf("Before sorting:\n");
    print_list_of_lists(&container);

    if (sort_sublists(&container) != 0) {
        fprintf(stderr, "Failed to sort sublists\n");
        goto cleanup;
    }

    printf("After sorting:\n");
    print_list_of_lists(&container);

    status = EXIT_SUCCESS;

cleanup:
    free_list_of_lists(&container);
    return status;
}