#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct WordNode {
    char *word;
    struct WordNode *next;
} WordNode;

WordNode *create_node(const char *word) {
    WordNode *node;
    size_t len;
    
    if (word == NULL) {
        return NULL;
    }
    
    len = strnlen(word, 1024);
    if (len == 1024) {
        return NULL;
    }
    
    node = (WordNode *)malloc(sizeof(WordNode));
    if (node == NULL) {
        return NULL;
    }
    
    node->word = (char *)malloc(len + 1);
    if (node->word == NULL) {
        free(node);
        return NULL;
    }
    
    memcpy(node->word, word, len);
    node->word[len] = '\0';
    node->next = NULL;
    return node;
}

void free_list(WordNode *head) {
    WordNode *current = head;
    WordNode *next;
    
    while (current != NULL) {
        next = current->next;
        free(current->word);
        free(current);
        current = next;
    }
}

WordNode *remove_words(WordNode *head, const char *word_to_remove) {
    WordNode *current;
    WordNode *previous;
    WordNode *to_delete;
    
    if (head == NULL || word_to_remove == NULL) {
        return head;
    }
    
    while (head != NULL && strcmp(head->word, word_to_remove) == 0) {
        to_delete = head;
        head = head->next;
        free(to_delete->word);
        free(to_delete);
    }
    
    if (head == NULL) {
        return NULL;
    }
    
    previous = head;
    current = head->next;
    
    while (current != NULL) {
        if (strcmp(current->word, word_to_remove) == 0) {
            to_delete = current;
            previous->next = current->next;
            current = current->next;
            free(to_delete->word);
            free(to_delete);
        } else {
            previous = current;
            current = current->next;
        }
    }
    
    return head;
}

void print_list(const WordNode *head) {
    const WordNode *current = head;
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
    WordNode *list = NULL;
    WordNode *temp = NULL;
    
    const char *words[] = {"red", "green", "blue", "black"};
    int num_words = sizeof(words) / sizeof(words[0]);
    int i;
    
    for (i = num_words - 1; i >= 0; i--) {
        temp = create_node(words[i]);
        if (temp == NULL) {
            free_list(list);
            return 1;
        }
        
        temp->next = list;
        list = temp;
    }
    
    printf("Original list: ");
    print_list(list);
    
    list = remove_words(list, "black");
    
    printf("After removing 'black': ");
    print_list(list);
    
    free_list(list);
    
    return 0;
}