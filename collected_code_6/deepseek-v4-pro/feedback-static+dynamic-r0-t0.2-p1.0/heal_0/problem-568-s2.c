#include <stdio.h>
#include <stdlib.h>

typedef struct Dictionary {
    int placeholder;
} Dictionary;

typedef struct DictNode {
    Dictionary *dict;
    struct DictNode *next;
} DictNode;

DictNode *create_empty_dict_list(int count) {
    DictNode *head = NULL;
    DictNode *tail = NULL;
    int i;

    for (i = 0; i < count; i++) {
        DictNode *new_node = (DictNode *)malloc(sizeof(DictNode));
        if (new_node == NULL) {
            DictNode *current = head;
            while (current != NULL) {
                DictNode *temp = current;
                current = current->next;
                free(temp->dict);
                free(temp);
            }
            return NULL;
        }

        new_node->dict = (Dictionary *)malloc(sizeof(Dictionary));
        if (new_node->dict == NULL) {
            free(new_node);
            DictNode *current = head;
            while (current != NULL) {
                DictNode *temp = current;
                current = current->next;
                free(temp->dict);
                free(temp);
            }
            return NULL;
        }

        new_node->dict->placeholder = 0;
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

void free_dict_list(DictNode *head) {
    DictNode *current = head;
    while (current != NULL) {
        DictNode *temp = current;
        current = current->next;
        free(temp->dict);
        free(temp);
    }
}

int main(void) {
    DictNode *list = create_empty_dict_list(5);
    if (list == NULL) {
        fprintf(stderr, "Failed to create dictionary list\n");
        return EXIT_FAILURE;
    }

    free_dict_list(list);
    return EXIT_SUCCESS;
}