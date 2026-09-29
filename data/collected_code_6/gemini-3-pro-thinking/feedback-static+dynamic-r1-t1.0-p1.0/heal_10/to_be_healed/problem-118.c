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
    if (str == NULL) {
        return NULL;
    }
    
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    
    new_node->data = (char *)malloc(len + 1);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    
    for (size_t i = 0; i <= len; i++) {
        new_node->data[i] = str[i];
    }
    
    new_node->next = NULL;
    
    return new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  */

Node* string_to_list(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    
    char *copy = (char *)malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i <= len; i++) {
        copy[i] = str[i];
    }

    Node *head = NULL;
    Node *tail = NULL;

    char *token = strtok(copy, " \t\n\r");
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
        token = strtok(NULL, " \t\n\r");
    }

    free(copy);
    return head;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            Node *list_head = string_to_list(argv[i]);
            printf("[");
            Node *current = list_head;
            while (current != NULL) {
                printf("'%s'", current->data);
                if (current->next != NULL) {
                    printf(", ");
                }
                current = current->next;
            }
            printf("]\n");
            free_list(list_head);
        }
        return EXIT_SUCCESS;
    }

    int buf_size = 4096;
    char *buffer = (char *)malloc((size_t)buf_size);
    if (buffer == NULL) {
        return EXIT_FAILURE;
    }
    
    while (fgets(buffer, buf_size, stdin) != NULL) {
        Node *list_head = string_to_list(buffer);

        printf("[");
        Node *current = list_head;
        while (current != NULL) {
            printf("'%s'", current->data);
            if (current->next != NULL) {
                printf(", ");
            }
            current = current->next;
        }
        printf("]\n");

        free_list(list_head);
    }

    free(buffer);
    return EXIT_SUCCESS;
}