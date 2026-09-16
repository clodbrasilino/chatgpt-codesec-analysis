#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    size_t length;
} List;

List *create_list() {
    List *list = malloc(sizeof(List));
    if (list == NULL) {
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->length = 0;
    return list;
}

void append_list(List *list, int value) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->next = NULL;
    if (list->head == NULL) {
        list->head = node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
    list->length++;
}

void free_list(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

List *find_min_length_list(List **lists, size_t count) {
    if (lists == NULL || count == 0) {
        return NULL;
    }
    List *min_list = lists[0];
    for (size_t i = 1; i < count; i++) {
        if (lists[i]->length < min_list->length) {
            min_list = lists[i];
        }
    }
    return min_list;
}

int main() {
    List *list1 = create_list();
    List *list2 = create_list();
    List *list3 = create_list();

    append_list(list1, 1);
    append_list(list1, 2);
    append_list(list1, 3);

    append_list(list2, 4);

    append_list(list3, 5);
    append_list(list3, 6);

    List *lists[] = {list1, list2, list3};
    size_t list_count = sizeof(lists) / sizeof(lists[0]);

    /* Possible weaknesses found:
     *  Variable 'min_list' can be declared as pointer to const [constVariablePointer]
     */
    List *min_list = find_min_length_list(lists, list_count);
    if (min_list != NULL) {
        printf("Minimum length: %zu\n", min_list->length);
    }

    for (size_t i = 0; i < list_count; i++) {
        free_list(lists[i]);
    }

    return 0;
}