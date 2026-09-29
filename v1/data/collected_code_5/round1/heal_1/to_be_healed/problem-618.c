#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
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

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;
    struct Node* result;

    push(&list1, 8);
    push(&list1, 6);
    push(&list2, 2);
    push(&list2, 3);

    /* Possible weaknesses found:
     *  Potential leak of memory pointed to by 'list2' [unix.Malloc]
     *  Potential leak of memory pointed to by 'list1' [unix.Malloc]
     */
    result = listDivide(list1, list2);
    
    if (result == NULL) {
        printf("Error! Division by zero or null list.\n");
        return 1;
    }

    /* Possible weaknesses found:
     *  Potential leak of memory pointed to by 'result' [unix.Malloc]
     */
    while (result != NULL) {
        printf("%d ", result->data);
        result = result->next;
    }
    return 0;
}

