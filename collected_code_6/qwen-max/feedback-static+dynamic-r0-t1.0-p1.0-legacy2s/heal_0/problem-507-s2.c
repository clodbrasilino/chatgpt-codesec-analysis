#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    char *word;
    struct ListNode *next;
} ListNode;

ListNode* create_node(char *data) {
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->word = strdup(data);
    newNode->next = NULL;
    return newNode;
}

void add_node(ListNode **head, char *data) {
    ListNode *newNode = create_node(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        ListNode *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

int remove_word(ListNode **head, const char *wordToRemove) {
    ListNode *current = *head;
    ListNode *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->word, wordToRemove) == 0) {
            if (previous == NULL) {
                *head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current->word);
            free(current);
            return 1; // Word removed
        }
        previous = current;
        current = current->next;
    }
    return 0; // Word not found
}

void print_list(ListNode *head) {
    while (head != NULL) {
        printf("%s -> ", head->word);
        head = head->next;
    }
    printf("NULL\n");
}

void free_list(ListNode *head) {
    ListNode *current = head;
    while (current != NULL) {
        ListNode *next = current->next;
        free(current->word);
        free(current);
        current = next;
    }
}

int main() {
    ListNode *head = NULL;
    
    add_node(&head, "apple");
    add_node(&head, "banana");
    add_node(&head, "cherry");
    add_node(&head, "date");
    
    printf("Original list: ");
    print_list(head);
    
    remove_word(&head, "banana");
    remove_word(&head, "date");

    printf("Modified list: ");
    print_list(head);

    free_list(head);
    return 0;
}