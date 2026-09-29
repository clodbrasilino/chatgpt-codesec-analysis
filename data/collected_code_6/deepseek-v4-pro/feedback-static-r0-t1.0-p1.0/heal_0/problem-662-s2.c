#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    char *value;
    struct Node *next;
} Node;

typedef struct Dictionary {
    Node *head;
    int size;
} Dictionary;

Dictionary *create_dictionary(void) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->head = NULL;
    dict->size = 0;
    return dict;
}

int insert(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }
    
    new_node->key = strdup(key);
    new_node->value = strdup(value);
    
    if (new_node->key == NULL || new_node->value == NULL) {
        free(new_node->key);
        free(new_node->value);
        free(new_node);
        return -1;
    }
    
    new_node->next = dict->head;
    dict->head = new_node;
    dict->size++;
    return 0;
}

Node *find_node(Dictionary *dict, const char *key) {
    if (dict == NULL || key == NULL) {
        return NULL;
    }
    
    Node *current = dict->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void sort_dictionary(Dictionary *dict) {
    if (dict == NULL || dict->head == NULL || dict->head->next == NULL) {
        return;
    }
    
    int swapped;
    Node *ptr1;
    Node *lptr = NULL;
    
    do {
        swapped = 0;
        ptr1 = dict->head;
        
        while (ptr1->next != lptr) {
            if (strcmp(ptr1->key, ptr1->next->key) > 0) {
                char *temp_key = ptr1->key;
                char *temp_value = ptr1->value;
                ptr1->key = ptr1->next->key;
                ptr1->value = ptr1->next->value;
                ptr1->next->key = temp_key;
                ptr1->next->value = temp_value;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void print_dictionary(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    
    Node *current = dict->head;
    while (current != NULL) {
        printf("%s: %s\n", current->key, current->value);
        current = current->next;
    }
}

void free_dictionary(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    
    Node *current = dict->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
    free(dict);
}

int main(void) {
    Dictionary *dict = create_dictionary();
    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return 1;
    }
    
    if (insert(dict, "banana", "fruit") != 0 ||
        insert(dict, "apple", "fruit") != 0 ||
        insert(dict, "cherry", "fruit") != 0 ||
        insert(dict, "date", "fruit") != 0) {
        fprintf(stderr, "Failed to insert into dictionary\n");
        free_dictionary(dict);
        return 1;
    }
    
    printf("Before sorting:\n");
    print_dictionary(dict);
    
    sort_dictionary(dict);
    
    printf("\nAfter sorting:\n");
    print_dictionary(dict);
    
    free_dictionary(dict);
    return 0;
}