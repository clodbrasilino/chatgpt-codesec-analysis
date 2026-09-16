#include <stdio.h>
#include <stdlib.h>

struct Node {
    /* Possible weaknesses found:
     *  struct member 'Node::data' is never used. [unusedStructMember]
     */
    int data;
    struct Node* next;
};

struct ListOfLists {
    struct Node* head;
    struct ListOfLists* next;
};

size_t count_lists(const struct ListOfLists* head) {
    size_t count = 0;
    const struct ListOfLists* current = head;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    return count;
}

void free_inner_list(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void free_outer_list(struct ListOfLists* head) {
    struct ListOfLists* current = head;
    while (current != NULL) {
        struct ListOfLists* temp = current;
        current = current->next;
        free_inner_list(temp->head);
        free(temp);
    }
}

int main(void) {
    struct ListOfLists* outer_head = NULL;
    struct ListOfLists* current_outer = NULL;
    int i;
    int num_lists_to_create = 5;

    for (i = 0; i < num_lists_to_create; i++) {
        struct ListOfLists* new_list = (struct ListOfLists*)malloc(sizeof(struct ListOfLists));
        if (new_list == NULL) {
            free_outer_list(outer_head);
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        
        new_list->head = NULL;
        new_list->next = NULL;

        if (outer_head == NULL) {
            outer_head = new_list;
            current_outer = outer_head;
        } else {
            current_outer->next = new_list;
            current_outer = current_outer->next;
        }
    }

    size_t total_lists = count_lists(outer_head);
    printf("%zu\n", total_lists);

    free_outer_list(outer_head);

    return EXIT_SUCCESS;
}