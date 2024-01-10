#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) {
        printf("Failed to allocate memory\n");
        exit(1);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void append(struct Node** head_ref, int data) {
    struct Node* new_node = newNode(data);
    struct Node* last = *head_ref;
    
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
}

void subtractLists(struct Node* list1, struct Node* list2) {
    struct Node* result = NULL;

    while (list1 != NULL) {
        struct Node* temp = list2;
        int exist = 0;

        while (temp != NULL) {
            if (list1->data == temp->data) {
                exist = 1;
                break;
            }
            temp = temp->next;
        }

        if (exist == 0) {
            append(&result, list1->data);
        }
        list1 = list1->next;
    }

    struct Node* temp = result;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    free(result);
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    append(&list1, 1);
    append(&list1, 2);
    append(&list1, 3);

    append(&list2, 2);
    append(&list2, 3);
    append(&list2, 4);

    subtractLists(list1, list2); 

    free(list1);
    free(list2);
    return 0;
}