#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void append(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    if (!new_node)
        return;

    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    struct Node* last = *head_ref;
    while (last->next)
        last = last->next;
    last->next = new_node;
}

char* concatenateList(struct Node* head) {
    char* result = calloc(10, sizeof(char));

    if (!result)
        return result;

    struct Node* current = head;
    size_t length = 1;
    while (current != NULL) {
        length += snprintf(NULL, 0, "%d", current->data);
        char* temp = realloc(result, length);

        if (!temp) {
            free(result);
            return NULL;
        }

        result = temp;
        snprintf(result + strlen(result), length, "%d", current->data);
        current = current->next;
    }

    return result;
}

int main() {
    struct Node* head = NULL;

    append(&head, 1);
    append(&head, 2);
    append(&head, 3);

    char* concatenatedString = concatenateList(head);

    if (concatenatedString) {
        printf("%s\n", concatenatedString);
        free(concatenatedString);
    }

    return 0;
}