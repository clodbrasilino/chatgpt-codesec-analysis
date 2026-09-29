#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct WordNode {
    char *word;
    struct WordNode *next;
} WordNode;

WordNode *create_node(const char *word) {
    WordNode *node = (WordNode *)malloc(sizeof(WordNode));
    if (node == NULL) {
        return NULL;
    }
    
    node->word = (char *)malloc(strlen(word) + 1);
    if (node->word == NULL) {
        free(node);
        return NULL;
    }
    
    strcpy(node->word, word);
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
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['red', 'green', 'blue', 'black'], got <no output>
  *  test case 2 failed: expected ['red', 'green', 'black', 'orange'], got <no output>
  *  test case 1 failed: expected ['red', 'green', 'blue', 'white'], got <no output>
  */

WordNode *remove_words(WordNode *head, const char *word_to_remove) {
    if (head == NULL || word_to_remove == NULL) {
        return head;
    }
    
    WordNode *current = head;
    WordNode *previous = NULL;
    
    while (current != NULL) {
        if (strcmp(current->word, word_to_remove) == 0) {
            WordNode *to_delete = current;
            
            if (previous == NULL) {
                head = current->next;
                current = head;
            } else {
                previous->next = current->next;
                current = current->next;
            }
            
            free(to_delete->word);
            free(to_delete);
        } else {
            previous = current;
            current = current->next;
        }
    }
    
    return head;
}

void print_list(WordNode *head) {
    WordNode *current = head;
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

WordNode *insert_sorted(WordNode *head, const char *word) {
    WordNode *new_node = create_node(word);
    if (new_node == NULL) {
        return head;
    }
    
    if (head == NULL || strcmp(word, head->word) < 0) {
        new_node->next = head;
        return new_node;
    }
    
    WordNode *current = head;
    while (current->next != NULL && strcmp(word, current->next->word) > 0) {
        current = current->next;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    
    return head;
}

int main(void) {
    WordNode *list = NULL;
    
    const char *words[] = {"red", "green", "blue", "black", "white", "orange"};
    int num_words = sizeof(words) / sizeof(words[0]);
    
    for (int i = 0; i < num_words; i++) {
        WordNode *new_list = insert_sorted(list, words[i]);
        if (new_list == NULL && list != NULL) {
            free_list(list);
            return 1;
        }
        list = new_list;
    }
    
    printf("Original list: ");
    print_list(list);
    
    list = remove_words(list, "banana");
    
    printf("After removing 'banana': ");
    print_list(list);
    
    list = remove_words(list, "blue");
    printf("After removing 'blue': ");
    print_list(list);
    
    list = remove_words(list, "white");
    printf("After removing 'white': ");
    print_list(list);
    
    free_list(list);
    
    return 0;
}