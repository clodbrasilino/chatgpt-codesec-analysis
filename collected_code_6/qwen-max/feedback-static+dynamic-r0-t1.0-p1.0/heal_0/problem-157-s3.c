#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char character;
    int count;
} Run;

typedef struct Node {
    Run run;
    struct Node *next;
} Node;

Node* create_node(char c, int count) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) return NULL;
    new_node->run.character = c;
    new_node->run.count = count;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

Node* run_length_encoding(const char *input) {
    if (input == NULL || *input == '\0') return NULL;
    
    Node *head = NULL;
    Node *tail = NULL;
    
    char last_char = *input;
    int count = 0;
    
    while (*input) {
        if (*input == last_char) {
            count++;
        } else {
            Node *new_node = create_node(last_char, count);
            if (new_node == NULL) {
                free_list(head);
                return NULL;
            }
            if (head == NULL) {
                head = new_node;
                tail = new_node;
            } else {
                tail->next = new_node;
                tail = new_node;
            }
            last_char = *input;
            count = 1;
        }
        input++;
    }
    
    Node *new_node = create_node(last_char, count);
    if (new_node == NULL) {
        free_list(head);
        return NULL;
    }
    if (head == NULL) {
        head = new_node;
    } else {
        tail->next = new_node;
    }
    
    return head;
}

void print_encoded(Node *head) {
    while (head != NULL) {
        printf("('%c', %d) ", head->run.character, head->run.count);
        head = head->next;
    }
    printf("\n");
}

int main() {
    const char *input = "aaabbcddd";
    Node *encoded = run_length_encoding(input);
    if (encoded != NULL) {
        print_encoded(encoded);
        free_list(encoded);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    return 0;
}