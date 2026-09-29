#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int type; // 0 for int, 1 for float, 2 for char
    union {
        int i;
        float f;
        char c;
    } data;
    struct Tuple *next;
} Tuple;

Tuple* removeDataType(Tuple *head, int type) {
    Tuple *current = head;
    Tuple *prev = NULL;

    while (current != NULL) {
        if (current->type == type) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            Tuple *temp = current;
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
    return head;
}

int main() {
    Tuple *head = malloc(sizeof(Tuple));
    head->type = 0;
    head->data.i = 10;
    head->next = malloc(sizeof(Tuple));
    head->next->type = 1;
    head->next->data.f = 20.0;
    head->next->next = malloc(sizeof(Tuple));
    head->next->next->type = 2;
    head->next->next->data.c = 'a';
    head->next->next->next = NULL;

    head = removeDataType(head, 1);

    Tuple *current = head;
    while (current != NULL) {
        if (current->type == 0) {
            printf("%d\n", current->data.i);
        } else if (current->type == 1) {
            printf("%f\n", current->data.f);
        } else if (current->type == 2) {
            printf("%c\n", current->data.c);
        }
        current = current->next;
    }

    while (head != NULL) {
        Tuple *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}