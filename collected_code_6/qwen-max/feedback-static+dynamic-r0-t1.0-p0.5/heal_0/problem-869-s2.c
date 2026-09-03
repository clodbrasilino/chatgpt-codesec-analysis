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
    lol->lists = (List**)calloc(count, sizeof(List*));
    if (!lol->lists) {
        free(lol);
        return NULL;
    }
    lol->count = count;
    return lol;
}

List* create_list(size_t size) {
    List *list = (List*)malloc(sizeof(List));
    if (!list) return NULL;
    list->data = (int*)calloc(size, sizeof(int));
    if (!list->data) {
        free(list);
        return NULL;
    }
    list->size = size;
    return list;
}

ListOfLists* filter_lists_in_range(ListOfLists *lol, int min, int max) {
    ListOfLists *filtered = create_list_of_lists(lol->count);
    if (!filtered) return NULL;

    size_t new_count = 0;
    for (size_t i = 0; i < lol->count; ++i) {
        int all_within_range = 1;
        for (size_t j = 0; j < lol->lists[i]->size; ++j) {
            if (lol->lists[i]->data[j] < min || lol->lists[i]->data[j] > max) {
                all_within_range = 0;
                break;
            }
        }
        if (all_within_range) {
            filtered->lists[new_count++] = lol->lists[i];
        } else {
            free_list(lol->lists[i]);
        }
    }

    filtered->count = new_count;
    return filtered;
}

int main() {
    ListOfLists *lol = create_list_of_lists(3);
    if (!lol) return 1;

    lol->lists[0] = create_list(3);
    if (!lol->lists[0]) goto cleanup;
    lol->lists[0]->data[0] = 1;
    lol->lists[0]->data[1] = 2;
    lol->lists[0]->data[2] = 3;

    lol->lists[1] = create_list(3);
    if (!lol->lists[1]) goto cleanup;
    lol->lists[1]->data[0] = 4;
    lol->lists[1]->data[1] = 5;
    lol->lists[1]->data[2] = 6;

    lol->lists[2] = create_list(3);
    if (!lol->lists[2]) goto cleanup;
    lol->lists[2]->data[0] = 7;
    lol->lists[2]->data[1] = 8;
    lol->lists[2]->data[2] = 9;

    ListOfLists *filtered = filter_lists_in_range(lol, 2, 5);
    if (!filtered) goto cleanup;

    for (size_t i = 0; i < filtered->count; ++i) {
        for (size_t j = 0; j < filtered->lists[i]->size; ++j) {
            printf("%d ", filtered->lists[i]->data[j]);
        }
        printf("\n");
    }

cleanup:
    free_list_of_lists(lol);
    if (filtered) free_list_of_lists(filtered);
    return 0;
}