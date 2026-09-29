#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int value;
    struct Tuple* next;
} Tuple;

int sum_alternate_chains(Tuple* head, int chain) {
    if (head == NULL) {
        return 0;
    }

    int total = 0;
    int index = 0;
    Tuple* current = head;

    while (current != NULL) {
        if ((index % 2) == chain) {
            total += current->value;
        }
        current = current->next;
        index++;
    }

    return total;
}

Tuple* create_tuple(int value) {
    Tuple* new_tuple = (Tuple*)malloc(sizeof(Tuple));
    if (new_tuple == NULL) {
        return NULL;
    }
    new_tuple->value = value;
    new_tuple->next = NULL;
    return new_tuple;
}

void free_tuple_list(Tuple* head) {
    Tuple* current = head;
    while (current != NULL) {
        Tuple* temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    Tuple* head = NULL;
    Tuple* tail = NULL;
    int values[] = {10, 20, 30, 40, 50, 60, 70, 80};
    int count = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < count; i++) {
        Tuple* new_tuple = create_tuple(values[i]);
        if (new_tuple == NULL) {
            free_tuple_list(head);
            return 1;
        }
        if (head == NULL) {
            head = new_tuple;
            tail = new_tuple;
        } else {
            tail->next = new_tuple;
            tail = new_tuple;
        }
    }

    int sum_chain0 = sum_alternate_chains(head, 0);
    int sum_chain1 = sum_alternate_chains(head, 1);

    printf("Sum of chain 0: %d\n", sum_chain0);
    printf("Sum of chain 1: %d\n", sum_chain1);

    free_tuple_list(head);
    return 0;
}