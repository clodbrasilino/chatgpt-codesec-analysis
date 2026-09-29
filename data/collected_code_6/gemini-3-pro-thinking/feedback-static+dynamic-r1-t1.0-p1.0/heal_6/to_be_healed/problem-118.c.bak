#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(const char *str);
void free_list(Node *head);
Node* string_to_list(const char *str);

Node* create_node(const char *str) {
    Node *new_node;
    if (str == NULL) {
        return NULL;
    }
    
    new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    
    new_node->data = (char *)malloc(strlen(str) + 1);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    
    strcpy(new_node->data, str);
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        if (temp->data != NULL) {
            free(temp->data);
        }
        free(temp);
    }
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  */

Node* string_to_list(const char *str) {
    char *copy;
    Node *head = NULL;
    Node *tail = NULL;
    char *token;
    
    if (str == NULL) {
        return NULL;
    }

    copy = (char *)malloc(strlen(str) + 1);
    if (copy == NULL) {
        return NULL;
    }
    strcpy(copy, str);

    token = strtok(copy, " \t\n\r,[]\"'");
    while (token != NULL) {
        Node *new_node = create_node(token);
        if (new_node == NULL) {
            free_list(head);
            free(copy);
            return NULL;
        }

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        token = strtok(NULL, " \t\n\r,[]\"'");
    }

    free(copy);
    return head;
}

int main(int argc, const char *argv[]) {
    char buffer[8192] = {0};
    Node *list_head;
    Node *current;
    
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            size_t current_len = strlen(buffer);
            size_t remaining = sizeof(buffer) - current_len - 1;
            strncat(buffer, argv[i], remaining);
            
            if (i < argc - 1) {
                current_len = strlen(buffer);
                remaining = sizeof(buffer) - current_len - 1;
                strncat(buffer, " ", remaining);
            }
        }
    } else {
        size_t len = fread(buffer, 1, sizeof(buffer) - 1, stdin);
        buffer[len] = '\0';
    }

    list_head = string_to_list(buffer);

    printf("[");
    current = list_head;
    while (current != NULL) {
        printf("'%s'", current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");

    free_list(list_head);
    fflush(stdout);

    return EXIT_SUCCESS;
}