#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    size_t length;
} List;

List *create_list() {
    List *list = malloc(sizeof(List));
    if (!list) return NULL;
    list->head = NULL;
    list->length = 0;
    return list;
}

void append_list(List *list, int data) {
    if (!list) return;
    Node *node = malloc(sizeof(Node));
    if (!node) return;
    node->data = data;
    node->next = NULL;
    if (!list->head) {
        list->head = node;
    } else {
        Node *curr = list->head;
        while (curr->next) curr = curr->next;
        curr->next = node;
    }
    list->length++;
}

void free_list(List *list) {
    if (!list) return;
    Node *curr = list->head;
    while (curr) {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
    free(list);
}

const List *find_max_length_list(List **lists, size_t count) {
    if (!lists || count == 0) return NULL;
    const List *max_list = lists[0];
    for (size_t i = 1; i < count; i++) {
        if (lists[i] && lists[i]->length > max_list->length) {
            max_list = lists[i];
        }
    }
    return max_list;
}

int main() {
    List *list1 = create_list();
    List *list2 = create_list();
    List *list3 = create_list();

    if (!list1 || !list2 || !list3) {
        free_list(list1);
        free_list(list2);
        free_list(list3);
        return 1;
    }

    append_list(list1, 1);
    append_list(list1, 2);
    append_list(list1, 3);

    append_list(list2, 4);
    append_list(list2, 5);

    append_list(list3, 6);
    append_list(list3, 7);
    append_list(list3, 8);
    append_list(list3, 9);

    List *lists[] = {list1, list2, list3};
    size_t count = sizeof(lists) / sizeof(lists[0]);

    const List *max_list = find_max_length_list(lists, count);

    if (max_list) {
        printf("Max length list length: %zu\n", max_list->length);
    }

    free_list(list1);
    free_list(list2);
    free_list(list3);

    return 0;
}