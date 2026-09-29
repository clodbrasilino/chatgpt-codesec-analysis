#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'new_node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

int maxSubList(struct Node* head) {
    int count = 0;
    int max = 0;

    while (head != NULL) {
        count++;
        if (count > max) {
            max = count;
        }
        head = head->next;
    }
    return max;
}

int main() {
    struct Node* head = NULL;
    push(&head, 20);
    push(&head, 4);
    push(&head, 15);
    push(&head, 10);
    push(&head, 85);

    printf("Length of maximum sublist is %d\n", maxSubList(head));

    return 0;
}