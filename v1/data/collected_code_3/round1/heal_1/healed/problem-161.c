#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        return;
    }
    
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void removeElements(struct Node** list1, struct Node* list2) {
    struct Node* temp = *list1;
    struct Node* prev = NULL;

    while (temp != NULL && list2 != NULL) {
        if (temp->data == list2->data) {
            if (prev == NULL) {
                *list1 = temp->next;
            } else {
                prev->next = temp->next;
            }
            struct Node* temp_to_free = temp;
            temp = temp->next;
            free(temp_to_free);
            list2 = list2->next;
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    push(&list1, 7);
    push(&list1, 2);
    push(&list1, 3);
    push(&list1, 4);

    push(&list2, 2);
    push(&list2, 4);

    printf("List 1 before removal of elements: ");
    printList(list1);

    removeElements(&list1, list2);

    printf("List 1 after removal of elements: ");
    printList(list1);

    return 0;
}