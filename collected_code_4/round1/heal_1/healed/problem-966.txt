#include <stdio.h>
#include <stdlib.h>

typedef struct tuple {
    int valid;
    int values[2];
} tuple;

typedef struct list {
    tuple *data;
    struct list *next;
} list;

list* remove_empty_tuple(list *head) {
    list *current = head;
    list *prev = NULL;
    
    while(current != NULL) {
        if(!current->data->valid) {
            if(prev != NULL) {
                prev->next = current->next;
            }
            else {
                head = current->next;
            }

            list *temp = current;
            current = current->next;
            free(temp->data);
            free(temp);
        }
        else {
            prev = current;
            current = current->next;
        }
    }
    
    return head;
}

int main() {
    list *head = (list *)malloc(sizeof(list));
    list *second = NULL;
    list *third = NULL;

    if(head != NULL) {
        head->data = (tuple *)malloc(sizeof(tuple));

        if(head->data != NULL) {
            head->data->valid = 1;
            second = (list *)malloc(sizeof(list));

            if(second != NULL) {
               head->next = second;
               second->data = (tuple *)malloc(sizeof(tuple));

               if(second->data != NULL) {
                   second->data->valid = 0;
                   third = (list *)malloc(sizeof(list));

                   if(third != NULL) {
                       second->next = third;
                       third->data = (tuple *)malloc(sizeof(tuple));

                       if(third->data != NULL) {
                           third->data->valid = 1;
                           third->next = NULL;
                       }
                   }
               }
            }
        }
    }

    head = remove_empty_tuple(head);

    list *current = head;
    while(current != NULL) {
        if(current->data != NULL) {
            printf("%d ", current->data->valid);
            current = current->next;
        }
    }

    return 0;
}