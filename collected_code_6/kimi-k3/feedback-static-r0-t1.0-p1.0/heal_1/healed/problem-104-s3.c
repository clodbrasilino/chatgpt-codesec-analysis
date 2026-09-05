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
    const char *const *sa = (const char *const *)a;
    const char *const *sb = (const char *const *)b;
    return strcmp(*sa, *sb);
}

int sort_sublists(ListOfLists *lol)
{
    size_t i;

    if (lol == NULL) {
        return -1;
    }
    if (lol->count > 0 && lol->lists == NULL) {
        return -1;
    }

    for (i = 0; i < lol->count; i++) {
        if (lol->lists[i].count > 0 && lol->lists[i].items == NULL) {
            return -1;
        }
        if (lol->lists[i].count > 1) {
            qsort(lol->lists[i].items, lol->lists[i].count,
                  sizeof(char *), compare_strings);
        }
    }
    return 0;
}

static char *duplicate_string(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    len = strlen(s) + 1;
    copy = (char *)malloc(len);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, s, len);
    return copy;
}

static void free_string_list(StringList *list)
{
    if (list == NULL) {
        return;
    }
    if (list->items != NULL) {
        size_t i;
        for (i = 0; i < list->count; i++) {
            free(list->items[i]);
        }
        free(list->items);
    }
    list->items = NULL;
    list->count = 0;
}

static void free_list_of_lists(ListOfLists *lol)
{
    if (lol == NULL) {
        return;
    }
    if (lol->lists != NULL) {
        size_t i;
        for (i = 0; i < lol->count; i++) {
            free_string_list(&lol->lists[i]);
        }
        free(lol->lists);
    }
    lol->lists = NULL;
    lol->count = 0;
}

static int init_string_list(StringList *list, const char *const *strings,
                            size_t count)
{
    size_t i;

    if (list == NULL) {
        return -1;
    }
    list->items = NULL;
    list->count = 0;

    if (count == 0) {
        return 0;
    }
    if (strings == NULL) {
        return -1;
    }

    list->items = (char **)calloc(count, sizeof(char *));
    if (list->items == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        list->items[i] = duplicate_string(strings[i]);
        if (list->items[i] == NULL) {
            list->count = i;
            free_string_list(list);
            return -1;
        }
    }
    list->count = count;
    return 0;
}

static void print_list_of_lists(const ListOfLists *lol)
{
    size_t i, j;

    if (lol == NULL) {
        return;
    }
    for (i = 0; i < lol->count; i++) {
        printf("[");
        for (j = 0; j < lol->lists[i].count; j++) {
            printf("\"%s\"%s", lol->lists[i].items[j],
                   (j + 1 < lol->lists[i].count) ? ", " : "");
        }
        printf("]\n");
    }
}

int main(void)
{
    static const char *const data0[] = {"banana", "apple", "cherry"};
    static const char *const data1[] = {"dog", "cat"};
    static const char *const data2[] = {"zebra", "lion", "elephant", "ant"};
    static const char *const data3[] = {"single"};
    static const char *const *all_data[] = {data0, data1, data2, data3, NULL};
    static const size_t all_counts[] = {3, 2, 4, 1, 0};
    const size_t num_lists = sizeof(all_counts) / sizeof(all_counts[0]);
    ListOfLists lol;
    size_t i;

    lol.lists = NULL;
    lol.count = 0;

    lol.lists = (StringList *)calloc(num_lists, sizeof(StringList));
    if (lol.lists == NULL) {
        fprintf(stderr, "Allocation failure\n");
        return EXIT_FAILURE;
    }
    lol.count = num_lists;

    for (i = 0; i < num_lists; i++) {
        if (init_string_list(&lol.lists[i], all_data[i], all_counts[i]) != 0) {
            fprintf(stderr, "Initialization failure\n");
            free_list_of_lists(&lol);
            return EXIT_FAILURE;
        }
    }

    printf("Before sorting:\n");
    print_list_of_lists(&lol);

    if (sort_sublists(&lol) != 0) {
        fprintf(stderr, "Sort failure\n");
        free_list_of_lists(&lol);
        return EXIT_FAILURE;
    }

    printf("\nAfter sorting:\n");
    print_list_of_lists(&lol);

    free_list_of_lists(&lol);
    return EXIT_SUCCESS;
}