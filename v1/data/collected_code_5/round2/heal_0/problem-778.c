#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int value;
    struct list *next;
} List;

List* packDuplicates(List *head) {
    if(head == NULL) return NULL;

    List *current = head, *prev = head;

    while (current != NULL) {
        if (prev->value != current->value) {
            List *temp = (List *)malloc(sizeof(List));
            
            if(temp == NULL) {
                printf("Memory allocation failed!\n");
                exit(1);
            }

            temp->value = current->value;
            temp->next = NULL;
            prev->next = temp;
            prev = temp;
        }
        current = current->next;
    }
    return head->next;
}

int main() {
    List *head = NULL, *prev = NULL;
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements: ");

    for(int i = 0; i < n; i++) {
        List *temp = (List *)malloc(sizeof(List));
        
        if(temp == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
        
        scanf("%d", &(temp->value));
        temp->next = NULL;

        if(head == NULL) head = temp;
        else prev->next = temp;
        
        prev = temp;
    }
    head = packDuplicates(head);

    printf("List after packing duplicates: ");
    while(head != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
    return 0;
}