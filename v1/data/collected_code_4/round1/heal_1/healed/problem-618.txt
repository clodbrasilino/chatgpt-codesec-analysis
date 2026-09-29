#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    if (new_node == NULL) {
        exit(-1);
    }
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

struct Node* listDivide(struct Node* list1, struct Node* list2) {
    if (list1 == NULL || list2 == NULL)
        return NULL;

    struct Node* result = NULL;
    struct Node* temp = list2;

    while (list1 != NULL) {
        while (temp != NULL) {
            if (temp->data == 0)
                return NULL;

            int division = list1->data / temp->data;
            push(&result, division);
            temp = temp->next;
        }
        list1 = list1->next;
    }
    return result;
}

void freeList(struct Node* head) {
    struct Node* tmp;

    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;
    struct Node* result;

    push(&list1, 8);
    push(&list1, 6);
    push(&list2, 2);
    push(&list2, 3);

    result = listDivide(list1, list2);

    if (result == NULL) {
        printf("Error! Division by zero or null list.\n");
        return 1;
    }

    while (result != NULL) {
        printf("%d ", result->data);
        result = result->next;
    }

    freeList(list1);
    freeList(list2);
    freeList(result);

    return 0;
}