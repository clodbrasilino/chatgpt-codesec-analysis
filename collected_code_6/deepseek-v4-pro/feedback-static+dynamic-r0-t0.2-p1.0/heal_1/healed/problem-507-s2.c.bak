#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct WordNode {
    char *word;
    struct WordNode *next;
} WordNode;

typedef struct {
    WordNode *head;
    size_t size;
} WordList;

WordList *word_list_create(void) {
    WordList *list = (WordList *)malloc(sizeof(WordList));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

int word_list_add(WordList *list, const char *word) {
    if (list == NULL || word == NULL) {
        return -1;
    }
    
    WordNode *new_node = (WordNode *)malloc(sizeof(WordNode));
    if (new_node == NULL) {
        return -1;
    }
    
    new_node->word = (char *)malloc(strlen(word) + 1);
    if (new_node->word == NULL) {
        free(new_node);
        return -1;
    }
    
    strcpy(new_node->word, word);
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        WordNode *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    
    list->size++;
    return 0;
}

void word_list_destroy(WordList *list) {
    if (list == NULL) {
        return;
    }
    
    WordNode *current = list->head;
    while (current != NULL) {
        WordNode *next = current->next;
        free(current->word);
        free(current);
        current = next;
    }
    
    free(list);
}

int word_list_remove(WordList *list, const char *word) {
    if (list == NULL || word == NULL || list->head == NULL) {
        return -1;
    }
    
    WordNode *current = list->head;
    WordNode *previous = NULL;
    
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            if (previous == NULL) {
                list->head = current->next;
            } else {
                previous->next = current->next;
            }
            
            free(current->word);
            free(current);
            list->size--;
            return 0;
        }
        
        previous = current;
        current = current->next;
    }
    
    return -1;
}

int word_list_remove_all(WordList *list, const char *word) {
    if (list == NULL || word == NULL) {
        return -1;
    }
    
    int removed_count = 0;
    
    while (word_list_remove(list, word) == 0) {
        removed_count++;
    }
    
    return removed_count;
}

void word_list_print(const WordList *list) {
    if (list == NULL) {
        return;
    }
    
    WordNode *current = list->head;
    while (current != NULL) {
        printf("%s ", current->word);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    WordList *list = word_list_create();
    if (list == NULL) {
        fprintf(stderr, "Failed to create word list\n");
        return 1;
    }
    
    word_list_add(list, "apple");
    word_list_add(list, "banana");
    word_list_add(list, "cherry");
    word_list_add(list, "apple");
    word_list_add(list, "date");
    word_list_add(list, "apple");
    
    printf("Original list: ");
    word_list_print(list);
    
    int removed = word_list_remove_all(list, "apple");
    printf("Removed %d occurrences of 'apple'\n", removed);
    
    printf("List after removal: ");
    word_list_print(list);
    
    word_list_destroy(list);
    
    return 0;
}