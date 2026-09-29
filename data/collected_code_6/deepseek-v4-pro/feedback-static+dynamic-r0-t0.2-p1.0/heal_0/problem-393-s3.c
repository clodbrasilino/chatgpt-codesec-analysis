#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    size_t length;
} List;

List *create_list(void) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->length = 0;
    return list;
}

int append_node(List *list, int data) {
    if (list == NULL) {
        return -1;
    }
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }
    new_node->data = data;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->length++;
    return 0;
}

void free_list(List *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

List *find_longest_list(List **lists, size_t count) {
    if (lists == NULL || count == 0) {
        return NULL;
    }
    
    List *longest = lists[0];
    size_t max_length = (longest != NULL) ? longest->length : 0;
    
    for (size_t i = 1; i < count; i++) {
        if (lists[i] != NULL && lists[i]->length > max_length) {
            longest = lists[i];
            max_length = lists[i]->length;
        }
    }
    
    return longest;
}

int main(void) {
    List *lists[3];
    
    lists[0] = create_list();
    lists[1] = create_list();
    lists[2] = create_list();
    
    if (lists[0] == NULL || lists[1] == NULL || lists[2] == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_list(lists[0]);
        free_list(lists[1]);
        free_list(lists[2]);
        return EXIT_FAILURE;
    }
    
    append_node(lists[0], 1);
    append_node(lists[0], 2);
    append_node(lists[0], 3);
    
    append_node(lists[1], 10);
    append_node(lists[1], 20);
    append_node(lists[1], 30);
    append_node(lists[1], 40);
    append_node(lists[1], 50);
    
    append_node(lists[2], 100);
    append_node(lists[2], 200);
    
    List *longest = find_longest_list(lists, 3);
    
    if (longest != NULL) {
        printf("Longest list length: %zu\n", longest->length);
        printf("Elements: ");
        Node *current = longest->head;
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    } else {
        printf("No valid lists found\n");
    }
    
    free_list(lists[0]);
    free_list(lists[1]);
    free_list(lists[2]);
    
    return EXIT_SUCCESS;
}