#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *data;
    struct Node *next;
};

void insertStringAtBeginning(struct Node *head, const char *prefix) {
    if (head == NULL || prefix == NULL) {
        return;
    }

    size_t prefix_len = strnlen(prefix, 1024);
    struct Node *current = head;

    while (current != NULL) {
        if (current->data != NULL) {
            size_t data_len = strnlen(current->data, 1024);
            char *new_data = malloc(prefix_len + data_len + 1);

            if (new_data != NULL) {
                snprintf(new_data, prefix_len + data_len + 1, "%s%s", prefix, current->data);
                free(current->data);
                current->data = new_data;
            }
        }
        current = current->next;
    }
}

int main(void) {
    struct Node *head = malloc(sizeof(struct Node));
    if (head == NULL) return 1;
    head->data = strdup("world");
    if (head->data == NULL) {
        free(head);
        return 1;
    }

    struct Node *second = malloc(sizeof(struct Node));
    if (second == NULL) {
        free(head->data);
        free(head);
        return 1;
    }
    second->data = strdup("people");
    if (second->data == NULL) {
        free(second);
        free(head->data);
        free(head);
        return 1;
    }
    
    head->next = second;
    second->next = NULL;

    insertStringAtBeginning(head, "Hello ");

    struct Node *current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }

    current = head;
    while (current != NULL) {
        struct Node *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }

    return 0;
}