#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    int count;
} StringList;

int compare_strings(const void *a, const void *b) {
    const char *str_a = *(const char * const *)a;
    const char *str_b = *(const char * const *)b;
    return strcmp(str_a, str_b);
}

void sort_sublists(StringList *lists, int list_count) {
    if (lists == NULL || list_count <= 0) {
        return;
    }

    for (int i = 0; i < list_count; i++) {
        if (lists[i].items != NULL && lists[i].count > 0) {
            qsort(lists[i].items, lists[i].count, sizeof(char *), compare_strings);
        }
    }
}

void free_string_list(StringList *list) {
    if (list == NULL) {
        return;
    }

    if (list->items != NULL) {
        for (int i = 0; i < list->count; i++) {
            free(list->items[i]);
            list->items[i] = NULL;
        }
        free(list->items);
        list->items = NULL;
    }
    list->count = 0;
}

void free_all_lists(StringList *lists, int list_count) {
    if (lists == NULL) {
        return;
    }

    for (int i = 0; i < list_count; i++) {
        free_string_list(&lists[i]);
    }
    free(lists);
}

int main(void) {
    StringList *lists = malloc(3 * sizeof(StringList));
    if (lists == NULL) {
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        lists[i].items = NULL;
        lists[i].count = 0;
    }

    lists[0].items = malloc(3 * sizeof(char *));
    if (lists[0].items == NULL) {
        free_all_lists(lists, 3);
        return 1;
    }
    lists[0].count = 3;
    lists[0].items[0] = strdup("banana");
    lists[0].items[1] = strdup("apple");
    lists[0].items[2] = strdup("cherry");

    lists[1].items = malloc(4 * sizeof(char *));
    if (lists[1].items == NULL) {
        free_all_lists(lists, 3);
        return 1;
    }
    lists[1].count = 4;
    lists[1].items[0] = strdup("dog");
    lists[1].items[1] = strdup("cat");
    lists[1].items[2] = strdup("elephant");
    lists[1].items[3] = strdup("bird");

    lists[2].items = malloc(2 * sizeof(char *));
    if (lists[2].items == NULL) {
        free_all_lists(lists, 3);
        return 1;
    }
    lists[2].count = 2;
    lists[2].items[0] = strdup("zebra");
    lists[2].items[1] = strdup("lion");

    sort_sublists(lists, 3);

    for (int i = 0; i < 3; i++) {
        printf("List %d: ", i);
        for (int j = 0; j < lists[i].count; j++) {
            printf("%s ", lists[i].items[j]);
        }
        printf("\n");
    }

    free_all_lists(lists, 3);

    return 0;
}