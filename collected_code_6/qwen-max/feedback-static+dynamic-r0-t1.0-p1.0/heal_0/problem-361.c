#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int *data;
    size_t size;
    struct list *next;
} List;

List* create_list() {
    return (List*)calloc(1, sizeof(List));
}

void free_list(List *head) {
    List *current = head;
    while (current != NULL) {
        if (current->data) {
            free(current->data);
        }
        List *temp = current;
        current = current->next;
        free(temp);
    }
}

List* remove_empty_lists(List *head) {
    List dummy;
    dummy.next = NULL;
    List *tail = &dummy;

    for (List *current = head; current != NULL; current = current->next) {
        if (current->size > 0) {
            tail->next = current;
            tail = current;
        }
    }
    tail->next = NULL;
    return dummy.next;
}

int main() {
    List *head = create_list();
    head->data = (int*)malloc(3 * sizeof(int));
    head->size = 3;
    head->data[0] = 1;
    head->data[1] = 2;
    head->data[2] = 3;

    List *second = create_list();
    second->data = NULL;
    second->size = 0;
    head->next = second;

    List *third = create_list();
    third->data = (int*)malloc(2 * sizeof(int));
    third->size = 2;
    third->data[0] = 4;
    third->data[1] = 5;
    second->next = third;

    List *fourth = create_list();
    fourth->data = NULL;
    fourth->size = 0;
    third->next = fourth;

    List *cleaned = remove_empty_lists(head);

    for (List *current = cleaned; current != NULL; current = current->next) {
        for (size_t i = 0; i < current->size; ++i) {
            printf("%d ", current->data[i]);
        }
        printf("\n");
    }

    free_list(cleaned);
    return 0;
}