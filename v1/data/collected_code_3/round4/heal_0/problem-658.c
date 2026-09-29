#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void insert(struct Node** head, int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data  = data;
    node->next = (*head);
    (*head)    = node;
}

int get_max_occurrence(struct Node* head) {
    struct Node* i = head;
    struct Node* j;
    int max_count = 0;
    int max_value;

    while (i != NULL && i->next != NULL) {
        int count = 1;
        j = i->next;
        while (j != NULL) {
            if (i->data == j->data)
                count++;
            j = j->next;
        }

        if (count > max_count) {
            max_count = count;
            max_value = i->data;
        }
        i = i->next;
    }

    return max_value;
}

int main() {
    struct Node* head = NULL;
    insert(&head, 20);
    insert(&head, 30);
    insert(&head, 40);
    insert(&head, 50);
    insert(&head, 30);
    insert(&head, 30);

    printf("Item with maximum occurrences is %d", get_max_occurrence(head));

    return 0;
}