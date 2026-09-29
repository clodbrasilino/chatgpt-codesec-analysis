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
    list *second = (list *)malloc(sizeof(list));
    list *third = (list *)malloc(sizeof(list));
    
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'head' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    head->data = (tuple *)malloc(sizeof(tuple));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*head.data' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    head->data->valid = 1;
    head->next = second;

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'second' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    second->data = (tuple *)malloc(sizeof(tuple));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*second.data' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    second->data->valid = 0;
    second->next = third;

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'third' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    third->data = (tuple *)malloc(sizeof(tuple));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*third.data' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    third->data->valid = 1;
    third->next = NULL;

    head = remove_empty_tuple(head);

    list *current = head;
    while(current != NULL) {
        printf("%d ", current->data->valid);
        current = current->next;
    }

    return 0;
}