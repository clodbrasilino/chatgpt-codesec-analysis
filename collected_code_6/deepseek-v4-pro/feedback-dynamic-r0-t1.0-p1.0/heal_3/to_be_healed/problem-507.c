#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *word;
    struct node *next;
} node_t;

node_t *create_node(const char *word) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->word = (char *)malloc(strlen(word) + 1);
    if (new_node->word == NULL) {
        free(new_node);
        return NULL;
    }
    strcpy(new_node->word, word);
    new_node->next = NULL;
    return new_node;
}

void free_list(node_t *head) {
    node_t *current = head;
    node_t *next;
    while (current != NULL) {
        next = current->next;
        free(current->word);
        free(current);
        current = next;
    }
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['red', 'green', 'black', 'orange'], got <no output>
  *  test case 1 failed: expected ['red', 'green', 'blue', 'white'], got <no output>
  *  test case 0 failed: expected ['red', 'green', 'blue', 'black'], got <no output>
  */

node_t *remove_words(node_t *head, const char *target) {
    if (head == NULL || target == NULL) {
        return head;
    }
    
    node_t dummy;
    dummy.next = head;
    node_t *prev = &dummy;
    node_t *current = head;
    
    while (current != NULL) {
        if (strcmp(current->word, target) == 0) {
            prev->next = current->next;
            free(current->word);
            free(current);
            current = prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }
    
    return dummy.next;
}

void print_list(node_t *head) {
    node_t *current = head;
    int first = 1;
    printf("[");
    while (current != NULL) {
        if (!first) {
            printf(", ");
        }
        printf("'%s'", current->word);
        first = 0;
        current = current->next;
    }
    printf("]\n");
}

int main(void) {
    node_t *head = NULL;
    node_t *tail = NULL;
    const char *words[] = {"red", "green", "blue", "black"};
    int count = sizeof(words) / sizeof(words[0]);
    int i;
    
    for (i = 0; i < count; i++) {
        node_t *new_node = create_node(words[i]);
        if (new_node == NULL) {
            free_list(head);
            return 1;
        }
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    
    printf("Original list: ");
    print_list(head);
    
    head = remove_words(head, "red");
    printf("After removing 'red': ");
    print_list(head);
    
    head = remove_words(head, "green");
    printf("After removing 'green': ");
    print_list(head);
    
    head = remove_words(head, "blue");
    printf("After removing 'blue': ");
    print_list(head);
    
    free_list(head);
    return 0;
}