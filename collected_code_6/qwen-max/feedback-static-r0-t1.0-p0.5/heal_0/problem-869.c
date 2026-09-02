#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *data;
    size_t size;
} List;

typedef struct ListOfLists {
    List **lists;
    size_t count;
} ListOfLists;

void free_list(List *list) {
    if (list->data) {
        free(list->data);
    }
    free(list);
}

void free_list_of_lists(ListOfLists *lol) {
    for (size_t i = 0; i < lol->count; ++i) {
        free_list(lol->lists[i]);
    }
    free(lol->lists);
    free(lol);
}

ListOfLists* create_list_of_lists(size_t count) {
    ListOfLists *lol = (ListOfLists*)malloc(sizeof(ListOfLists));
    if (!lol) return NULL;
    lol->lists = (List**)malloc(count * sizeof(List*));
    if (!lol->lists) {
        free(lol);
        return NULL;
    }
    lol->count = count;
    for (size_t i = 0; i < count; ++i) {
        lol->lists[i] = (List*)malloc(sizeof(List));
        if (!lol->lists[i]) {
            free_list_of_lists(lol);
            return NULL;
        }
        lol->lists[i]->data = NULL;
        lol->lists[i]->size = 0;
    }
    return lol;
}

int add_to_list(List *list, int value) {
    list->data = (int*)realloc(list->data, (list->size + 1) * sizeof(int));
    if (!list->data) return -1;
    list->data[list->size++] = value;
    return 0;
}

ListOfLists* filter_lists_in_range(ListOfLists *lol, int min, int max) {
    ListOfLists *filtered = create_list_of_lists(lol->count);
    if (!filtered) return NULL;
    size_t new_count = 0;
    for (size_t i = 0; i < lol->count; ++i) {
        int in_range = 1;
        for (size_t j = 0; j < lol->lists[i]->size; ++j) {
            if (lol->lists[i]->data[j] < min || lol->lists[i]->data[j] > max) {
                in_range = 0;
                break;
            }
        }
        if (in_range) {
            filtered->lists[new_count] = (List*)malloc(sizeof(List));
            if (!filtered->lists[new_count]) {
                free_list_of_lists(filtered);
                return NULL;
            }
            filtered->lists[new_count]->data = (int*)malloc(lol->lists[i]->size * sizeof(int));
            if (!filtered->lists[new_count]->data) {
                free_list(filtered->lists[new_count]);
                free_list_of_lists(filtered);
                return NULL;
            }
            for (size_t j = 0; j < lol->lists[i]->size; ++j) {
                filtered->lists[new_count]->data[j] = lol->lists[i]->data[j];
            }
            filtered->lists[new_count]->size = lol->lists[i]->size;
            new_count++;
        }
    }
    filtered->count = new_count;
    return filtered;
}

int main() {
    ListOfLists *lol = create_list_of_lists(5);
    if (!lol) return 1;

    add_to_list(lol->lists[0], 1);
    add_to_list(lol->lists[0], 2);
    add_to_list(lol->lists[1], 3);
    add_to_list(lol->lists[1], 4);
    add_to_list(lol->lists[2], 5);
    add_to_list(lol->lists[2], 6);
    add_to_list(lol->lists[3], 7);
    add_to_list(lol->lists[3], 8);
    add_to_list(lol->lists[4], 9);
    add_to_list(lol->lists[4], 10);

    ListOfLists *filtered = filter_lists_in_range(lol, 3, 7);
    if (!filtered) {
        free_list_of_lists(lol);
        return 1;
    }

    for (size_t i = 0; i < filtered->count; ++i) {
        for (size_t j = 0; j < filtered->lists[i]->size; ++j) {
            printf("%d ", filtered->lists[i]->data[j]);
        }
        printf("\n");
    }

    free_list_of_lists(lol);
    free_list_of_lists(filtered);
    return 0;
}