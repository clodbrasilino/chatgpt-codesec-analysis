#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *data;
    struct Node *next;
};

void free_list(struct Node *head) {
    while (head != NULL) {
        struct Node *tmp = head;
        head = head->next;
        free(tmp->data);
        free(tmp);
    }
}

char* concatenate_list(struct Node *head) {
    if (head == NULL) {
        char *empty_str = malloc(1);
        if (empty_str != NULL) {
            empty_str[0] = '\0';
        }
        return empty_str;
    }

    size_t total_length = 0;
    struct Node *current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            total_length += strlen(current->data);
        }
        current = current->next;
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            strcat(result, current->data);
        }
        current = current->next;
    }

    return result;
}

int main(void) {
    struct Node *head = malloc(sizeof(struct Node));
    if (head == NULL) {
        return 1;
    }
    
    struct Node *second = malloc(sizeof(struct Node));
    if (second == NULL) {
        free(head);
        return 1;
    }

    struct Node *third = malloc(sizeof(struct Node));
    if (third == NULL) {
        free(head);
        free(second);
        return 1;
    }

    head->data = strdup("Hello, ");
    head->next = second;

    second->data = strdup("world");
    second->next = third;

    third->data = strdup("!");
    third->next = NULL;

    if (head->data == NULL || second->data == NULL || third->data == NULL) {
        free_list(head);
        return 1;
    }

    char *concatenated = concatenate_list(head);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    }

    free_list(head);

    return 0;
}