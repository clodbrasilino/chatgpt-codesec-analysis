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

void sort_sublists(ListOfLists *list_of_lists)
{
    size_t i;

    if (list_of_lists == NULL || list_of_lists->lists == NULL) {
        return;
    }

    for (i = 0; i < list_of_lists->count; i++) {
        StringList *sublist = &list_of_lists->lists[i];
        if (sublist->items != NULL && sublist->count > 1) {
            qsort(sublist->items, sublist->count, sizeof(char *), compare_strings);
        }
    }
}

static char *duplicate_string(const char *str)
{
    size_t len;
    char *copy;

    if (str == NULL) {
        return NULL;
    }

    len = strlen(str) + 1;
    copy = (char *)malloc(len);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, str, len);
    return copy;
}

static int init_string_list(StringList *list, const char **strings, size_t count)
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
            size_t j;
            for (j = 0; j < i; j++) {
                free(list->items[j]);
            }
            free(list->items);
            list->items = NULL;
            return -1;
        }
        list->count++;
    }

    return 0;
}

static void free_string_list(StringList *list)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (list == NULL) {
        return;
    }

    if (list->items != NULL) {
        for (i = 0; i < list->count; i++) {
            free(list->items[i]);
        }
        free(list->items);
        list->items = NULL;
    }
    list->count = 0;
}

static int init_list_of_lists(ListOfLists *lol, size_t count)
{
    if (lol == NULL) {
        return -1;
    }

    lol->lists = NULL;
    lol->count = 0;

    if (count == 0) {
        return 0;
    }

    lol->lists = (StringList *)calloc(count, sizeof(StringList));
    if (lol->lists == NULL) {
        return -1;
    }

    lol->count = count;
    return 0;
}

static void free_list_of_lists(ListOfLists *lol)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (lol == NULL) {
        return;
    }

    if (lol->lists != NULL) {
        for (i = 0; i < lol->count; i++) {
            free_string_list(&lol->lists[i]);
        }
        free(lol->lists);
        lol->lists = NULL;
    }
    lol->count = 0;
}

static void print_list_of_lists(const ListOfLists *lol)
{
    size_t i, j;

    if (lol == NULL) {
        return;
    }

    for (i = 0; i < lol->count; i++) {
        printf("Sublist %zu: [", i);
        for (j = 0; j < lol->lists[i].count; j++) {
            printf("\"%s\"", lol->lists[i].items[j]);
            if (j + 1 < lol->lists[i].count) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

int main(void)
{
    ListOfLists lol;
    const char *data0[] = {"banana", "apple", "cherry", "date"};
    const char *data1[] = {"zebra", "lion", "elephant", "tiger", "bear"};
    const char *data2[] = {"red", "green", "blue"};
    const char *data3[] = {"single"};
    int status = EXIT_FAILURE;

    if (init_list_of_lists(&lol, 4) != 0) {
        fprintf(stderr, "Failed to initialize list of lists\n");
        return EXIT_FAILURE;
    }

    if (init_string_list(&lol.lists[0], data0, 4) != 0) {
        fprintf(stderr, "Failed to initialize sublist 0\n");
        goto cleanup;
    }

    if (init_string_list(&lol.lists[1], data1, 5) != 0) {
        fprintf(stderr, "Failed to initialize sublist 1\n");
        goto cleanup;
    }

    if (init_string_list(&lol.lists[2], data2, 3) != 0) {
        fprintf(stderr, "Failed to initialize sublist 2\n");
        goto cleanup;
    }

    if (init_string_list(&lol.lists[3], data3, 1) != 0) {
        fprintf(stderr, "Failed to initialize sublist 3\n");
        goto cleanup;
    }

    printf("Before sorting:\n");
    print_list_of_lists(&lol);

    sort_sublists(&lol);

    printf("\nAfter sorting:\n");
    print_list_of_lists(&lol);

    status = EXIT_SUCCESS;

cleanup:
    free_list_of_lists(&lol);
    return status;
}