#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct List {
    struct Node* head;
    size_t length;
};

struct List* find_min_length_list(struct List** lists, size_t num_lists) {
    if (lists == NULL || num_lists == 0) {
        return NULL;
    }

    struct List* min_list = NULL;
    size_t min_length = (size_t)-1;

    for (size_t i = 0; i < num_lists; ++i) {
        if (lists[i] != NULL) {
            if (min_list == NULL || lists[i]->length < min_length) {
                min_list = lists[i];
                min_length = lists[i]->length;
            }
        }
    }

    return min_list;
}

void free_list(struct List* list) {
    if (list != NULL) {
        struct Node* current = list->head;
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
        free(list);
    }
}

struct List* create_list(size_t length) {
    struct List* list = (struct List*)malloc(sizeof(struct List));
    if (list == NULL) {
        return NULL;
    }

    list->length = length;
    list->head = NULL;

    struct Node* tail = NULL;
    for (size_t i = 0; i < length; ++i) {
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        if (new_node == NULL) {
            free_list(list);
            return NULL;
        }
        new_node->data = (int)i;
        new_node->next = NULL;

        if (list->head == NULL) {
            list->head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    return list;
}

int main(void) {
    size_t num_lists = 3;
    struct List** lists = (struct List**)malloc(num_lists * sizeof(struct List*));
    if (lists == NULL) {
        return EXIT_FAILURE;
    }

    lists[0] = create_list(5);
    lists[1] = create_list(2);
    lists[2] = create_list(8);

    int allocation_failed = 0;
    for (size_t i = 0; i < num_lists; ++i) {
        if (lists[i] == NULL) {
            allocation_failed = 1;
            break;
        }
    }

    if (!allocation_failed) {
        struct List* min_list = find_min_length_list(lists, num_lists);
        if (min_list != NULL) {
            printf("Minimum length is %zu\n", min_list->length);
        }
    }

    for (size_t i = 0; i < num_lists; ++i) {
        free_list(lists[i]);
    }
    free(lists);

    return allocation_failed ? EXIT_FAILURE : EXIT_SUCCESS;
}