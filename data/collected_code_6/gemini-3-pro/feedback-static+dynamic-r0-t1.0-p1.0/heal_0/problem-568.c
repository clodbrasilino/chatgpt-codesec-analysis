#include <stdio.h>
#include <stdlib.h>

typedef struct Dictionary {
    void* dummy; 
} Dictionary;

typedef struct Node {
    Dictionary* dict;
    struct Node* next;
} Node;

Node* create_dictionary_list(size_t num_dicts) {
    if (num_dicts == 0) {
        return NULL;
    }

    Node* head = NULL;
    Node* tail = NULL;

    for (size_t i = 0; i < num_dicts; ++i) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        if (!new_node) {
            Node* current = head;
            while (current) {
                Node* next = current->next;
                free(current->dict);
                free(current);
                current = next;
            }
            return NULL;
        }

        new_node->dict = (Dictionary*)malloc(sizeof(Dictionary));
        if (!new_node->dict) {
            free(new_node);
            Node* current = head;
            while (current) {
                Node* next = current->next;
                free(current->dict);
                free(current);
                current = next;
            }
            return NULL;
        }

        new_node->dict->dummy = NULL;
        new_node->next = NULL;

        if (!head) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    return head;
}

void free_dictionary_list(Node* head) {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        free(current->dict);
        free(current);
        current = next;
    }
}

int main(void) {
    size_t num_dicts = 5;
    Node* dict_list = create_dictionary_list(num_dicts);

    if (dict_list) {
        free_dictionary_list(dict_list);
    }

    return 0;
}