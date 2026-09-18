#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    char* value;
    struct Tuple* next;
} Tuple;

Tuple* RemoveTuples(Tuple* head, int k) {
    Tuple* current = head;
    Tuple* prev = NULL;

    while (current != NULL) {
        if (strlen(current->value) == k) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }

            Tuple* temp = current;
            current = current->next;

            free(temp->value);
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }

    return head;
}

void AddTuple(Tuple** head, char* value) {
    Tuple* newTuple = (Tuple*) malloc(sizeof(Tuple));

    if (newTuple == NULL) {
        return;
    }

    newTuple->value = malloc(strlen(value) + 1);

    if (newTuple->value == NULL) {
        free(newTuple);
        return;
    }

    newTuple->next = *head;
    strcpy(newTuple->value, value);
    *head = newTuple;
}

int main() {
    Tuple* head = NULL;

    AddTuple(&head, "Test");
    AddTuple(&head, "Hello");
    AddTuple(&head, "World");

    head = RemoveTuples(head, 5);

    Tuple* current = head;
    while (current != NULL) {
        printf("%s\n", current->value);
        current = current->next;
    }

    while(head != NULL) {
        Tuple* temp = head;
        head = head->next;
        free(temp->value);
        free(temp);
    }

    return 0;
}