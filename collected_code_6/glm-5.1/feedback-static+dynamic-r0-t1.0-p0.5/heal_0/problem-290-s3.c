#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    size_t length;
} List;

typedef struct ListOfLists {
    List **lists;
    size_t count;
    size_t capacity;
} ListOfLists;

ListOfLists *find_max_length_lists(ListOfLists *source) {
    if (source == NULL || source->count == 0) {
        return NULL;
    }

    size_t max_len = 0;
    for (size_t i = 0; i < source->count; i++) {
        if (source->lists[i] != NULL && source->lists[i]->length > max_len) {
            max_len = source->lists[i]->length;
        }
    }

    if (max_len == 0) {
        return NULL;
    }

    size_t result_count = 0;
    for (size_t i = 0; i < source->count; i++) {
        if (source->lists[i] != NULL && source->lists[i]->length == max_len) {
            result_count++;
        }
    }

    ListOfLists *result = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (result == NULL) {
        return NULL;
    }

    result->lists = (List **)malloc(result_count * sizeof(List *));
    if (result->lists == NULL) {
        free(result);
        return NULL;
    }

    result->count = result_count;
    result->capacity = result_count;

    size_t index = 0;
    for (size_t i = 0; i < source->count; i++) {
        if (source->lists[i] != NULL && source->lists[i]->length == max_len) {
            result->lists[index++] = source->lists[i];
        }
    }

    return result;
}

List *create_list(size_t length) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->length = length;
    return list;
}

void free_list(List *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void free_list_of_lists(ListOfLists *lol) {
    if (lol == NULL) {
        return;
    }
    free(lol->lists);
    free(lol);
}

int main(void) {
    ListOfLists source;
    source.count = 5;
    source.capacity = 5;
    source.lists = (List **)malloc(source.capacity * sizeof(List *));
    if (source.lists == NULL) {
        return EXIT_FAILURE;
    }

    source.lists[0] = create_list(2);
    source.lists[1] = create_list(5);
    source.lists[2] = create_list(5);
    source.lists[3] = create_list(3);
    source.lists[4] = create_list(1);

    if (source.lists[0] == NULL || source.lists[1] == NULL || 
        source.lists[2] == NULL || source.lists[3] == NULL || 
        source.lists[4] == NULL) {
        for (size_t i = 0; i < source.count; i++) {
            free_list(source.lists[i]);
        }
        free(source.lists);
        return EXIT_FAILURE;
    }

    ListOfLists *max_lists = find_max_length_lists(&source);

    if (max_lists != NULL) {
        printf("Max length lists count: %zu\n", max_lists->count);
        for (size_t i = 0; i < max_lists->count; i++) {
            printf("List %zu length: %zu\n", i, max_lists->lists[i]->length);
        }
        free_list_of_lists(max_lists);
    }

    for (size_t i = 0; i < source.count; i++) {
        free_list(source.lists[i]);
    }
    free(source.lists);

    return EXIT_SUCCESS;
}