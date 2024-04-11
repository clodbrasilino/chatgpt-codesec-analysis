#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

float toFloat(char *str) {
    return strtof(str, NULL);
}

void convertListToFloat(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%f\n", toFloat(current->data));
        current = current->next;
    }
}

int main() {
    Node *head = malloc(sizeof(Node));
    if (head == NULL) {
        return 1;
    }
    
    Node *second = malloc(sizeof(Node));
    if (second == NULL) {
        free(head);
        return 1;
    }
    
    Node *third = malloc(sizeof(Node));
    if (third == NULL) {
        free(head);
        free(second);
        return 1;
    }

    head->data = "3.14";
    head->next = second;

    second->data = "2.71";
    second->next = third;

    third->data = "1.41";
    third->next = NULL;

    convertListToFloat(head);

    free(head);
    free(second);
    free(third);

    return 0;
}