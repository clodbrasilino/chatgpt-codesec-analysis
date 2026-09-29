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

List *find_max_length_list(List **lists, size_t count) {
    if (!lists || count == 0) return NULL;
    List *max_list = lists[0];
    for (size_t i = 1; i < count; i++) {
        if (lists[i]->length > max_list->length) {
            max_list = lists[i];
        }
    }
    return max_list;
}

int main() {
    List *lists[3];
    for (int i = 0; i < 3; i++) {
        lists[i] = create_list();
        if (!lists[i]) {
            for (int j = 0; j < i; j++) free_list(lists[j]);
            return 1;
        }
    }

    append_list(lists[0], 1);
    append_list(lists[0], 2);

    append_list(lists[1], 3);
    append_list(lists[1], 4);
    append_list(lists[1], 5);

    append_list(lists[2], 6);

    List *max_list = find_max_length_list(lists, 3);
    if (max_list) {
        printf("Max length: %zu\n", max_list->length);
    }

    for (int i = 0; i < 3; i++) {
        free_list(lists[i]);
    }

    return 0;
}