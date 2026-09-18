#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

size_t count_valid_lists(struct Node** lists, size_t array_size) {
    size_t count = 0;
    
    if (lists == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < array_size; ++i) {
        if (lists[i] != NULL) {
            count++;
        }
    }
    
    return count;
}

void free_list(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    size_t array_size = 3;
    struct Node** lists = (struct Node**)malloc(array_size * sizeof(struct Node*));
    
    if (lists == NULL) {
        return EXIT_FAILURE;
    }

    lists[0] = (struct Node*)malloc(sizeof(struct Node));
    if (lists[0] != NULL) {
        lists[0]->data = 1;
        lists[0]->next = NULL;
    }

    lists[1] = NULL;

    lists[2] = (struct Node*)malloc(sizeof(struct Node));
    if (lists[2] != NULL) {
        lists[2]->data = 2;
        lists[2]->next = NULL;
    }

    size_t valid_count = count_valid_lists(lists, array_size);
    printf("%zu\n", valid_count);

    for (size_t i = 0; i < array_size; ++i) {
        free_list(lists[i]);
    }
    free(lists);

    return EXIT_SUCCESS;
}