#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    void *data;
    int is_list;
    struct Node *next;
} Node;

int count_lists_in_tuple(Node *tuple_head) {
    int count = 0;
    Node *current = tuple_head;
    while (current != NULL) {
        if (current->is_list) {
            count++;
        }
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    return count;
}

int main() {
    Node *n1 = (Node *)malloc(sizeof(Node));
    Node *n2 = (Node *)malloc(sizeof(Node));
    Node *n3 = (Node *)malloc(sizeof(Node));
    if (n1 == NULL || n2 == NULL || n3 == NULL) {
        free(n1);
        free(n2);
        free(n3);
        return 1;
    }
    n1->data = NULL;
    n1->is_list = 0;
    n1->next = n2;
    n2->data = (void *)0x1;
    n2->is_list = 1;
    n2->next = n3;
    n3->data = (void *)0x2;
    n3->is_list = 1;
    n3->next = NULL;
    int result = count_lists_in_tuple(n1);
    printf("%d\n", result);
    return 0;
}