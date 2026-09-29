#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

Node* string_to_list(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    Node *head = NULL;
    Node *tail = NULL;
    const char *p = str;
    
    while (*p != '\0') {
        while (*p != '\0' && isspace((unsigned char)*p)) {
            p++;
        }
        
        if (*p == '\0') {
            break;
        }
        
        const char *start = p;
        while (*p != '\0' && !isspace((unsigned char)*p)) {
            p++;
        }
        
        size_t len = (size_t)(p - start);
        char *word = (char*)malloc(len + 1);
        if (word == NULL) {
            free_list(head);
            return NULL;
        }
        
        memcpy(word, start, len);
        word[len] = '\0';
        
        Node *new_node = (Node*)malloc(sizeof(Node));
        if (new_node == NULL) {
            free(word);
            free_list(head);
            return NULL;
        }
        
        new_node->data = word;
        new_node->next = NULL;
        
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    
    return head;
}

void print_list(Node *head) {
    Node *current = head;
    int first = 1;
    
    printf("[");
    while (current != NULL) {
        if (!first) {
            printf(", ");
        }
        printf("'%s'", current->data);
        first = 0;
        current = current->next;
    }
    printf("]\n");
}

int main(void) {
    const char *str = "python programming";
    
    Node *list = string_to_list(str);
    
    if (list == NULL) {
        printf("[]\n");
        return EXIT_SUCCESS;
    }
    
    print_list(list);
    free_list(list);
    
    return EXIT_SUCCESS;
}