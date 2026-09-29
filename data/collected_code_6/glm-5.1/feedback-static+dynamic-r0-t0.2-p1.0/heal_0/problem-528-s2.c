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
} ListOfLists;

ListOfLists *find_min_length_lists(ListOfLists *input) {
    if (input == NULL || input->count == 0) {
        return NULL;
    }

    size_t min_len = (size_t)-1;
    size_t result_count = 0;
    size_t i;

    for (i = 0; i < input->count; i++) {
        if (input->lists[i] != NULL && input->lists[i]->length < min_len) {
            min_len = input->lists[i]->length;
            result_count = 1;
        } else if (input->lists[i] != NULL && input->lists[i]->length == min_len) {
            result_count++;
        }
    }

    if (min_len == (size_t)-1) {
        return NULL;
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

    result->count = 0;

    for (i = 0; i < input->count; i++) {
        if (input->lists[i] != NULL && input->lists[i]->length == min_len) {
            result->lists[result->count] = input->lists[i];
            result->count++;
        }
    }

    return result;
}

List *create_list(size_t length) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->length = length;
    list->head = NULL;
    if (length > 0) {
        list->head = (Node *)malloc(sizeof(Node));
        if (list->head == NULL) {
            free(list);
            return NULL;
        }
        Node *current = list->head;
        size_t i;
        for (i = 1; i < length; i++) {
            current->next = (Node *)malloc(sizeof(Node));
            if (current->next == NULL) {
                Node *temp = list->head;
                while (temp != NULL) {
                    Node *next = temp->next;
                    free(temp);
                    temp = next;
                }
                free(list);
                return NULL;
            }
            current = current->next;
        }
        current->next = NULL;
    }
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
    if (lol->lists != NULL) {
        size_t i;
        for (i = 0; i < lol->count; i++) {
            free_list(lol->lists[i]);
        }
        free(lol->lists);
    }
    free(lol);
}

int main(void) {
    ListOfLists *input = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (input == NULL) {
        return 1;
    }

    input->count = 4;
    input->lists = (List **)malloc(input->count * sizeof(List *));
    if (input->lists == NULL) {
        free(input);
        return 1;
    }

    input->lists[0] = create_list(5);
    input->lists[1] = create_list(2);
    input->lists[2] = create_list(2);
    input->lists[3] = create_list(4);

    if (input->lists[0] == NULL || input->lists[1] == NULL || input->lists[2] == NULL || input->lists[3] == NULL) {
        free_list_of_lists(input);
        return 1;
    }

    ListOfLists *result = find_min_length_lists(input);

    if (result != NULL) {
        size_t i;
        for (i = 0; i < result->count; i++) {
            printf("List %zu length: %zu\n", i, result->lists[i]->length);
        }
        free(result->lists);
        free(result);
    }

    free_list_of_lists(input);

    return 0;
}