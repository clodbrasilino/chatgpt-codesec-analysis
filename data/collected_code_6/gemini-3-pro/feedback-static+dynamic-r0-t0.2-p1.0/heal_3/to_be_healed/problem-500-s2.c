#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

char* concatenate_list(Node *head) {
    if (head == NULL) {
        char *empty_str = malloc(1);
        if (empty_str != NULL) {
            empty_str[0] = '\0';
        }
        return empty_str;
    }

    size_t total_length = 0;
    Node *current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            total_length += strlen(current->data);
        }
        current = current->next;
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    char *dest_ptr = result;
    size_t remaining_space = total_length + 1;
    
    current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(current->data);
            
            if (len < remaining_space) {
                size_t i;
                for (i = 0; i < len; i++) {
                    dest_ptr[i] = current->data[i];
                }
                dest_ptr += len;
                remaining_space -= len;
            }
        }
        current = current->next;
    }
    *dest_ptr = '\0';

    return result;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node *node1 = malloc(sizeof(Node));
    Node *node2 = malloc(sizeof(Node));
    Node *node3 = malloc(sizeof(Node));

    if (node1 == NULL || node2 == NULL || node3 == NULL) {
        free(node1);
        free(node2);
        free(node3);
        return 1;
    }

    node1->data = "Hello, ";
    node1->next = node2;

    node2->data = "World";
    node2->next = node3;

    node3->data = "!";
    node3->next = NULL;

    char *concatenated = concatenate_list(node1);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    }

    free_list(node1);

    return 0;
}