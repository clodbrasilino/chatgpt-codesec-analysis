#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

void free_list(Node* head);
int string_to_list(const char* str, Node** out_head);
void print_list(const Node* head);

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

int string_to_list(const char* str, Node** out_head) {
    Node* head = NULL;
    Node* tail = NULL;

    if (str == NULL || out_head == NULL) {
        return -1;
    }

    *out_head = NULL;

    while (*str != '\0') {
        Node* new_node = (Node*)malloc(sizeof(Node));
        if (new_node == NULL) {
            free_list(head);
            return -1;
        }

        new_node->data = *str;
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }

        str++;
    }

    *out_head = head;
    return 0;
}

void print_list(const Node* head) {
    const Node* current = head;
    while (current != NULL) {
        putchar(current->data);
        current = current->next;
    }
    putchar('\n');
}

int main(void) {
    const char* my_string = "Hello, World!";
    Node* list = NULL;
    
    if (string_to_list(my_string, &list) == 0) {
        print_list(list);
        free_list(list);
        list = NULL;
    } else {
        fprintf(stderr, "Failed to convert string to list.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}