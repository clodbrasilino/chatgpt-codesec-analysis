#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

Node** split_every_nth(Node* head, int n, int* list_count) {
    if (head == NULL || n <= 0) {
        *list_count = 0;
        return NULL;
    }

    *list_count = 0;
    Node** lists = (Node**)malloc(10 * sizeof(Node*));
    if (lists == NULL) {
        return NULL;
    }
    for (int i = 0; i < 10; ++i) {
        lists[i] = NULL;
    }

    int current_list = 0;
    Node* current = head;
    Node* prev = NULL;

    while (current != NULL) {
        if (current_list >= 10) {
            Node** new_lists = (Node**)realloc(lists, (current_list + 1) * sizeof(Node*));
            if (new_lists == NULL) {
                for (int i = 0; i < current_list; ++i) {
                    free_list(lists[i]);
                }
                free(lists);
                *list_count = 0;
                return NULL;
            }
            lists = new_lists;
            lists[current_list] = NULL;
        }

        if (lists[current_list] == NULL) {
            lists[current_list] = current;
        } else {
            prev->next = current;
        }
        prev = current;

        current_list++;
        if (current_list % n == 0) {
            prev->next = NULL;
            prev = NULL;
        }

        current = current->next;
    }

    *list_count = (current_list + n - 1) / n;
    return lists;
}

int main() {
    Node* head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);
    head->next->next->next->next = create_node(5);

    int list_count;
    Node** lists = split_every_nth(head, 2, &list_count);

    for (int i = 0; i < list_count; ++i) {
        Node* current = lists[i];
        while (current != NULL) {
            printf("%d ", current->value);
            current = current->next;
        }
        printf("\n");
    }

    for (int i = 0; i < list_count; ++i) {
        free_list(lists[i]);
    }
    free(lists);

    return 0;
}