#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char **keys;
    char **values;
    size_t size;
    size_t capacity;
} Dictionary;

typedef struct ListNode {
    Dictionary *dict;
    struct ListNode *next;
} ListNode;

Dictionary* create_empty_dictionary(void) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }
    dict->keys = NULL;
    dict->values = NULL;
    dict->size = 0;
    dict->capacity = 0;
    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) {
        return;
    }
    free(dict->keys);
    free(dict->values);
    free(dict);
}

void free_dictionary_list(ListNode *head) {
    ListNode *current = head;
    while (current != NULL) {
        ListNode *next = current->next;
        free_dictionary(current->dict);
        free(current);
        current = next;
    }
}

ListNode* create_dictionary_list(size_t count) {
    ListNode *head = NULL;
    ListNode *tail = NULL;

    for (size_t i = 0; i < count; i++) {
        Dictionary *dict = create_empty_dictionary();
        if (!dict) {
            free_dictionary_list(head);
            return NULL;
        }

        ListNode *node = (ListNode*)malloc(sizeof(ListNode));
        if (!node) {
            free_dictionary(dict);
            free_dictionary_list(head);
            return NULL;
        }

        node->dict = dict;
        node->next = NULL;

        if (!head) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    return head;
}

int main(void) {
    size_t list_size = 5;
    
    ListNode *dict_list = create_dictionary_list(list_size);
    if (!dict_list) {
        fprintf(stderr, "Failed to create dictionary list.\n");
        return EXIT_FAILURE;
    }

    free_dictionary_list(dict_list);

    return EXIT_SUCCESS;
}