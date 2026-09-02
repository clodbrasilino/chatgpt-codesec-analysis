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

List* create_list(size_t size) {
    List *list = (List *)malloc(sizeof(List));
    list->data = (int *)malloc(size * sizeof(int));
    list->size = size;
    return list;
}

void free_list(List *list) {
    free(list->data);
    free(list);
}

ListOfLists* create_list_of_lists(size_t count) {
    ListOfLists *lol = (ListOfLists *)malloc(sizeof(ListOfLists));
    lol->lists = (List **)malloc(count * sizeof(List *));
    lol->count = count;
    for (size_t i = 0; i < count; ++i) {
        lol->lists[i] = NULL;
    }
    return lol;
}

void free_list_of_lists(ListOfLists *lol) {
    for (size_t i = 0; i < lol->count; ++i) {
        if (lol->lists[i]) {
            free_list(lol->lists[i]);
        }
    }
    free(lol->lists);
    free(lol);
}

ListOfLists* remove_outside_range(ListOfLists *lol, int min, int max) {
    ListOfLists *result = create_list_of_lists(lol->count);
    size_t new_count = 0;

    for (size_t i = 0; i < lol->count; ++i) {
        List *current = lol->lists[i];
        if (current && current->size > 0) {
            int all_in_range = 1;
            for (size_t j = 0; j < current->size; ++j) {
                if (current->data[j] < min || current->data[j] > max) {
                    all_in_range = 0;
                    break;
                }
            }
            if (all_in_range) {
                result->lists[new_count++] = current;
            } else {
                free_list(current);
            }
        }
    }

    result->count = new_count;
    return result;
}

int main() {
    ListOfLists *lol = create_list_of_lists(3);

    lol->lists[0] = create_list(3);
    lol->lists[0]->data[0] = 1;
    lol->lists[0]->data[1] = 2;
    lol->lists[0]->data[2] = 3;

    lol->lists[1] = create_list(3);
    lol->lists[1]->data[0] = 4;
    lol->lists[1]->data[1] = 5;
    lol->lists[1]->data[2] = 6;

    lol->lists[2] = create_list(3);
    lol->lists[2]->data[0] = 7;
    lol->lists[2]->data[1] = 8;
    lol->lists[2]->data[2] = 9;

    ListOfLists *filtered = remove_outside_range(lol, 2, 6);

    for (size_t i = 0; i < filtered->count; ++i) {
        for (size_t j = 0; j < filtered->lists[i]->size; ++j) {
            printf("%d ", filtered->lists[i]->data[j]);
        }
        printf("\n");
    }

    free_list_of_lists(filtered);
    free_list_of_lists(lol);

    return 0;
}